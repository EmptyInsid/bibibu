package database

type DataBase interface {
	getNumberOfAllUsers() (int, error)
	getNumberOfUserOnCourse(course string) (int, error)
	getProgressOnCourse(course string) (int, error)
	getNumberOfUserStartCourse(course string) (int, error)
	getNumberOfUserStartAll() (int, error)
	getInfoFirstTime() (int, error)
	getInfoSecondTime() (int, error)
	getCourseStat(course string) (int, error)
	getAllStat() (int, error)
}
