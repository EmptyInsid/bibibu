package main

import (
	tgClient "awesomeProject/client/telegram"
	"awesomeProject/consumer/event-consumer"
	"awesomeProject/events/telegram"
	"awesomeProject/storage/sqlite"
	"context"
	"flag"
	"log"
)

//6281142983:AAFcpPP7nX8IKK6oiB47SOxMi95uI_ImzX8

const (
	tgBotHost      = "api.telegram.org"
	sqlStoragePath = "data/sqlite/storage.db"
	batchSize      = 100
)

func main() {

	//s:=files.New(storagePath)
	s, err := sqlite.New(sqlStoragePath)
	if err != nil {
		log.Fatal("can't connect to storage: ", err)
	}
	//не определились какой контекст нужен
	if err := s.Init(context.TODO()); err != nil {
		log.Fatal("can't init storage: ", err)
	}

	eventsProcessor := telegram.New(
		tgClient.New(tgBotHost, mustToken()),
		s,
	)

	log.Print("service started")
	consumer := event_consumer.New(eventsProcessor, eventsProcessor, batchSize)
	if err := consumer.Start(); err != nil {
		log.Fatal("service is stopped", err)
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
