#include <iostream>	// подключает функции ввода вывода
#include <sstream>
#include <iomanip>  // подключает библиотеку работы с потаками записи
#include <string>	// подключает библиотеку строк
#include <vector>	// подключает библиотеку вкторов
#include <map>		// подключает библиотеку словарей
#include <set>		// подключает библиотеку множеств
//#include <algorithm>	// подключает стандартные функции (min, max, count)
//#include <fstream>  // подключает библиотеку ввода/вывода из/в файлов/ы
#include <iomanip>  // подключает библиотеку работы с потаками записи
using namespace std;


//Если дата не соответствует формату Год-Месяц-День, где 
		//----Год, Месяц и День — произвольные целые числа, 
		//то программа должна напечатать «Wrong date format: DATE», где 
		//----DATE — это то, что пользователь ввёл вместо даты (до пробела). 
		//Обратите внимание, что части даты разделяются ровно одним дефисом, 
		//а сама дата не должна содержать лишних символов ни перед годом, ни после дня. 
		//Части даты не могут быть пустыми, но могут быть нулевыми(только год) и даже отрицательными (только год).
			//Если формат даты верен, необходимо проверить валидность месяца и дня.
			//--Если номер месяца не является числом от 1 до 12, выведите «Month value is invalid: MONTH», 
			//	где MONTH — это неверный номер месяца, например, 13 или -1.
			//--Если месяц корректен, а день не лежит в диапазоне от 1 до 31, выведите «Day value is invalid: DAY», 
			//	где DAY — это неверный номер дня в месяце, например, 39 или 0.
		//Значение года проверять отдельно не нужно.
		//Не нужно проверять календарную корректность даты: количество дней в каждом месяце считается равным 31, високосные года учитывать не нужно.
		//Если неверны как месяц, так и день, то нужно вывести одно сообщение об ошибке в месяце.
			//	1-1-1 — корректная дата;
			//	-1-1-1 — корректная дата (год -1, месяц 1, день 1);
			//	1--1-1 — дата в верном формате, но с некорректным месяцем -1;
			//	1---1-1 — дата в неверном формате: месяц не может начинаться с двух дефисов.
			//	1-+1-+1 — корректная дата, так как +1 это целое число
class Date {
public:
	/*Date() {
		data = "0-1-1";
	};
	*/
	Date(string DATE) {
		date = DATE;
		ReadDate(DATE);
	}

	void exseption1() const {
		throw logic_error("Wrong date format: " + date);
	}

	void CheckSimbol(istream& stream) const {
		char ch;
		stream >> ch;
		if (ch != '-') {
			{ exseption1(); }//throw invalid_argument("Wrong date format: " + date);
		}
	}
	int GetYear() const { return year; }
	int GetMonth() const { return month; }
	int GetDay() const { return day; }
private:
	void ReadDate(string date) {
		stringstream stream(date);
			stream >> year;
			if (!stream) { exseption1();}//{ throw invalid_argument("Wrong date format: " + date); }
			CheckSimbol(stream);
			stream >> month;
			if (!stream) { exseption1(); }//{ throw invalid_argument("Wrong date format: " + date); }
			CheckSimbol(stream);
			stream >> day;
			if (!stream) { exseption1(); }//{ throw invalid_argument("Wrong date format: " + date); }

		stringstream stream2(date);
		stream2.ignore(date.size() - 1);
		int last = 0;
		stream2 >> last;
		if (last != abs(day % 10)) { exseption1(); }//{ throw invalid_argument("Wrong date format: " + date); }

		if (month > 12 || month < 1) { throw logic_error("Month value is invalid: " + to_string(month)); }

		if (day > 31 || day < 1) { throw logic_error("Day value is invalid: " + to_string(day)); }
	}
	int year, month, day;
	string date;
};


//Даты должны быть отформатированы специальным образом: 
//----ГГГГ-ММ-ДД : Г, М, Д — это цифры чисел года, месяца и дня соответственно. 
//Если какое-то число имеет меньше разрядов, то оно должно дополняться нулями, 
//------ 0001-01-01 — первое января первого года. 
//Вам не понадобится выводить дату с отрицательным значением года.
ostream& operator<<(ostream& stream, const Date& hs) {
	stream << setfill('0');
	stream	<< setw(4) << hs.GetYear() << '-'
			<< setw(2) << hs.GetMonth() << '-'
			<< setw(2) << hs.GetDay();
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) { return lhs.GetYear() < rhs.GetYear(); }
	else {
		if (lhs.GetMonth() != rhs.GetMonth()) {
			return lhs.GetMonth() < rhs.GetMonth();
		}
		else { return lhs.GetDay() < rhs.GetDay(); }
	}
}

class Database {
public:
	void Read_command(string str) {
		string command, DATE, event;
		stringstream stream(str);
		stream >> command;
		if (stream){
			if (command == "Add" || command == "Del" || command == "Find") {
				stream >> DATE;
				Date date(DATE);//, date2("1235-5-12"), date3("3000-12-12"), date4("1235-8-12"), date5("1235-5-30");
				if (command == "Find") {
					Find(date);
				}
				else {
					stream >> event;
					if (!stream && command == "Del") {
						//Программа всегда должна выводить строку вида «Deleted N events», где
						//---N — это количество всех найденных и удалённых событий. 
						//---N может быть равно нулю, если в указанную дату не было ни одного события.
						cout << "Deleted " << DeleteDate(date) << " events" << endl;
					}
					else {
						//В случае КОРРЕКТНОГО ввода программа ничего не должна выводить на экран.
						if (command == "Add") { AddEvent(date, event); }
						else {
							//Если событие найдено и удалено, программа должна вывести строку «Deleted successfully» (без кавычек).
							//Если событие в указанную дату не найдено, программа должна вывести строку «Event not found» (без кавычек).
							if (DeleteEvent(date, event)) {
								cout << "Deleted successfully" << endl;
							}
							else { cout << "Event not found" << endl; }
						}
					}
				}
			}
			else if (command == "Print") {
				Print();
			}
			//Если пользователь ввёл неизвестную команду, то программа должна об этом сообщить, 
			//выведя строку «Unknown command: COMMAND», где
			//---- COMMAND — это та команда, которую ввёл пользователь. 
			//Командой считается первое слово в строке (до пробела).
			else { throw logic_error("Unknown command: " + command); }
		}
	}

	void AddEvent(const Date& date, const string& event) {	// добавление события : Add Дата Событие
		//Добавление события БД
		//Если событие для данной даты уже существует, повторное его добавление нужно игнорировать.
		//В случае КОРРЕКТНОГО ввода программа ничего не должна выводить на экран.
		data_event[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {	// удаление события : Del Дата Событие
		//Удалить добавленное ранее событие с указанным именем в указанную дату, если оно существует.
		if (data_event.count(date) == 1) {
			if (data_event.at(date).count(event) == 1) {
				data_event[date].erase(event);
				if (data_event.at(date).empty()) { data_event.erase(date); }
				return true;
			}
		}
		return false;
	}
	int  DeleteDate(const Date& date) {	// удаление всех событий за конкретную дату : Del Дата
		//Команда удаляет все ранее добавленные события за указанную дату. 
		//Программа всегда должна выводить строку вида «Deleted N events», где
		//---N — это количество всех найденных и удалённых событий. 
		//---N может быть равно нулю, если в указанную дату не было ни одного события.
		int N = 0;
		if (data_event.count(date) == 1) {
			for (const auto& j : data_event.at(date)) {
				++N;
			}
			data_event.erase(date);
			return N;
		}
		else { return 0; }
	}
	void Find(const Date& date) {	// поиск событий за конкретную дату : Find Дата
		//Найти и распечатать ранее добавленные события в указанную дату. 
		//Программа должна вывести на печать только сами события, по одному на строке. 
		//События должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string).
		if (data_event.count(date) == 1) {
			for (const auto& j : data_event.at(date)) {
				cout << j << endl;
			}
		}
	}
	void Print() const {	// печать всех событий за все даты : Print
		//Программа должна вывести на печать все пары Дата Событие по одной на строке. 
		//------несколько событий в дате1: дата1 событие1 /n дата1 событие2 /n
		//Все пары должны быть отсортированы по дате, 
		//------события в рамках одной даты должны быть отсортированы по возрастанию 
		//		в порядке сравнения строк между собой (тип string). 
		if (!data_event.empty()) {
			for (const auto& i : data_event) {
				for (const auto& j : i.second) {
					cout << i.first << " " << j << endl;
				}
			}
		}

	}

private:
	map <Date, set<string>> data_event;	// пары вида: дата, событие
	// дата - строка - Год-Месяц-День, где Год, Месяц и День — целые числа
	// Событие - строка - произвольные печатные символы без разделителей внутри (пробелов, табуляций и пр.)
	// ---Событие не может быть пустой строкой
	// ---В одну и ту же дату может произойти много разных событий
	// ---Одинаковые события, произошедшие в один и тот же день, сохранять не нужно
};


//Все команды, даты и события при вводе разделены пробелами. 
//Команды считываются из стандартного ввода. 
//В одной строке может быть ровно одна команда, но можно ввести несколько команд в несколько строк.
//На вход также могут поступать пустые строки — их следует игнорировать и продолжать обработку новых команд в последующих строках.

//Гарантируется что:
//--Каждая команда занимает целиком ровно одну строку, хотя во вводе могут быть и пустые строки (их нужно игнорировать).
//--События всегда содержат указанное количество аргументов: 
//	после команды Add всегда следуют дата и событие, 
//	после команды Find всегда следует дата, 
//	после команды Del всегда следует дата и, возможно, событие, 
//	команда Print не содержит дополнительной информации.
//--Все команды, даты и события являются непустыми строками и 
//	не содержат пробелов и прочих пробельных символов. 
//	(В частности, наши тесты не содержат команды «Add 2018-02-12», 
//	потому что в ней после даты отсутствует название события.)
//	С другой стороны, команда Del может не содержать события после даты: 
//	в этом случае нужно удалить все события за указанную дату (см. раздел «Удаление нескольких событий»).
//--Несмотря на то, что дата с отрицательным значением года считается корректной, тесты устроены так, 
//	что её НЕ понадобится выводить в команде Print.

int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
		try {
			db.Read_command(command);// Считайте команды с потока ввода и обработайте каждую
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	return 0;
}
