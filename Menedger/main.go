package Menedger

import (
	"flag"
	"fmt"
	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
	"log"
	"os"
	"reflect"
)

const (
	tgBotHost      = "api.telegram.org"
	sqlStoragePath = "data/database/storage.db"
	batchSize      = 100
)

func main() {

	bot, err := tgbotapi.NewBotAPI(mustToken())
	if err != nil {
		log.Panic(err)
	}
	bot.Debug = true
	log.Print("service started")

	u := tgbotapi.NewUpdate(0)
	u.Timeout = 60

	updates := bot.GetUpdatesChan(u)

	for update := range updates {
		if update.Message == nil {
			continue
		}
		if reflect.TypeOf(update.Message.Text).Kind() == reflect.String && update.Message.Text != "" {
			switch update.Message.Text {
			case "/start":

				msg := tgbotapi.NewMessage(update.Message.Chat.ID, msgHello)
				bot.Send(msg)

			case "/all_number_of_users":

				if os.Getenv("DB_SWITCH") == "on" {
					num, err := getNumberOfAllUsers()
					if err != nil {
						//Отправлем сообщение
						msg := tgbotapi.NewMessage(update.Message.Chat.ID, "Database error.")
						bot.Send(msg)
					}
					ans := fmt.Sprintf("%d peoples used me for search information in Wikipedia", num)
					msg := tgbotapi.NewMessage(update.Message.Chat.ID, ans)
					bot.Send(msg)
				} else {
					msg := tgbotapi.NewMessage(update.Message.Chat.ID, msgDisconnect)
					bot.Send(msg)
				}
			case "/number_of_users_on_course":
			case "/progress_of_users_on_course":
			case "/all_progress_of_users":
			case "/all_number_of_users_start":
			case "/number_of_users_start_course":
			case "/info_about_first_time":
			case "/info_about_second_time":
			case "/all_stat_course":
			case "/all_start":
			default:
				msg := tgbotapi.NewMessage(update.Message.Chat.ID, msgUnknownCommand)
				bot.Send(msg)
			}
		} else {
			msg := tgbotapi.NewMessage(update.Message.Chat.ID, msgNoText)
			bot.Send(msg)
		}
	}
}

// function get token from client
func mustToken() string {
	token := flag.String(
		"tg-bot-token",
		"",
		"token for access to telegram bot",
	)
	flag.Parse()

	if *token == "" {
		log.Fatal("token is not specified")
	}
	return *token
}
