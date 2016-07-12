/**
*	By: TheCorPlay (Fernando Pérez Gutiérrez)
*	E-Mail: thecorplay@gmail.com
*	Current version: v1.1.0
*	_______________________________
*	INFORMATION
*
*	This project has been undertaken to assist in comparing files.
*	It is especially useful when it comes to large amounts of data,
*	as problems in programming contests...
*	_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*
*	All user information is given in Spanish/English.
*	If you need a translation to your language
*	or have made your own translation, contact me.
*	_______________________________
*	
*	COPYRIGHT ©
*
*	This file has copyright assigned.
*	It is free to use, but you can not distribute.
*
*	https://github.com/TheCorPlay
*/

#include <iostream> // Because use the console
#include <fstream> // Because read from files
#include <stdlib.h> // Because of the "limpiar;" method.

using namespace std;


// If you have another SO, like iOS add your definition
#ifdef _WIN32
#define limpiar system("cls");
#endif
 
#ifdef linux
#define limpiar system("clear");
#endif

const string INTRODUCE_ESP = "Introduce los dos ficheros a comparar, separados por espacios.\n";
const string DIFFERENCE_ESP = "//---- Diferencias en la linea ";
const string LENGTH_ERROR1_ESP = "No corresponde la longitud de ambos ficheros, \"";
const string LENGTH_ERROR2_ESP = "\" es mas largo que \"";
const string FAILS_ESP = "Numero de fallos: ";
const string SAME_ESP = "Archivos identicos.\n";
const string LIMIT_ERRORS_ESP = "Se han llegado al limite de errores. Demasiados fallos (";
const string FILES_NOT_FOUND_ESP = "No se han encontrado los archivos especificados, intentalo de nuevo. \n";
const string CONTINUE_ESP = "Continuar? [s/n] ";
const string CREDITS_ESP = "Programa hecho exclusivamente por: \n 	Fernando Perez Gutierrez \n 	Version 1.1.0\n";
const string UNKNOWN_COMMAND_ESP = "Comando desconocido. Usa \\h o \\help para mas informacion.\n";
const string COMMANDS_ESP = "Lista de comandos: \n 1- Help: \\help o \\h. Muestra todos los comandos.\n 2- Limit: \\limit o \\l. Estableces un limite de errores (0 = infinito).\n 3- Repeat: \\repeat o \\re. Vuelve a comparar los mismos ficheros.\n 4- Language: \\language o \\la. Cambia el idioma del programa (English\\Spanish).\n 5- Ignore: \\ignore o \\i. Ignora las diferencias por espacios [True\\false].\n 6- Exit: \\exit o \\e. Cierra correctamente la aplicacion.\n 7- Credits: \\credits o \\c. Muestra los creditos.\n";

const string INTRODUCE_EN = "Enter the two files to compare, separated by spaces.\n";
const string DIFFERENCE_EN = "//---- Differences in the line ";
const string LENGTH_ERROR1_EN = "They are not the same length both files, \"";
const string LENGTH_ERROR2_EN = "\" it is longer than \"";
const string FAILS_EN = "Number of fails: ";
const string SAME_EN = "Identical files.\n";
const string LIMIT_ERRORS_EN = "They have reached the limit of errors. Too many failures (";
const string FILES_NOT_FOUND_EN = "Not found the specified files, try again. \n";
const string CONTINUE_EN = "Continue? [s/n] ";
const string CREDITS_EN = "Program made exclusively by: \n 	Fernando Perez Gutierrez \n 	Version 1.1.0\n";
const string UNKNOWN_COMMAND_EN = "Unknown command. Use \\h or \\help for more information.\n";
const string COMMANDS_EN = "List of commands: \n 1- Help: \\help o \\h. Displays all commands.\n 2- Limit: \\limit o \\l. Set a limit error (0 = infinity).\n 3- Repeat: \\repeat o \\re. Again compare the same files.\n 4- Language: \\language o \\la. Change the program language (English\\Spanish).\n 5- Ignore: \\ignore o \\i. Ignore spaces differences [True \\ false].\n 6- Exit: \\exit o \\e. Shuts down the application.\n 7- Credits: \\credits o \\c. Dysplays the credits.\n";
							
struct Language {
	string introduce;
	string difference;
	string length_error1;
	string length_error2;
	string fails;
	string same;
	string limit_errors;
	string files_not_found;
	string continue_;
	string credits;
	string unknown;
	string commands;

	Language () {
		introduce = INTRODUCE_ESP;
		difference = DIFFERENCE_ESP;
		length_error1 = LENGTH_ERROR1_ESP;
		length_error2 = LENGTH_ERROR2_ESP;
		fails = FAILS_ESP;
		same = SAME_ESP;
		limit_errors = LIMIT_ERRORS_ESP;
		files_not_found = FILES_NOT_FOUND_ESP;
		continue_ = CONTINUE_ESP;
		credits = CREDITS_ESP;
		unknown = UNKNOWN_COMMAND_ESP;
		commands = COMMANDS_ESP;
	}
	
	void changeLanguage (string language) {
		if (language == "Spanish" || language == "spanish" || language == "español" || language == "Español") {
			introduce = INTRODUCE_ESP;
			difference = DIFFERENCE_ESP;
			length_error1 = LENGTH_ERROR1_ESP;
			length_error2 = LENGTH_ERROR2_ESP;
			fails = FAILS_ESP;
			same = SAME_ESP;
			limit_errors = LIMIT_ERRORS_EN;
			files_not_found = FILES_NOT_FOUND_ESP;
			continue_ = CONTINUE_ESP;
			credits = CREDITS_ESP;
			unknown = UNKNOWN_COMMAND_ESP;
			commands = COMMANDS_ESP;
		}
		else if (language == "English" || language == "english" || language == "ingles" || language == "Ingles") {
			introduce = INTRODUCE_EN;
			difference = DIFFERENCE_EN;
			length_error1 = LENGTH_ERROR1_EN;
			length_error2 = LENGTH_ERROR2_EN;
			fails = FAILS_EN;
			same = SAME_EN;
			files_not_found = FILES_NOT_FOUND_EN;
			continue_ = CONTINUE_EN;
			credits = CREDITS_EN;
			unknown = UNKNOWN_COMMAND_EN;
			commands = COMMANDS_EN;
		}
	}
};

// Return if both string are equal ignoring the spaces
bool difEspIgnore (string a, string b) {
	unsigned int i = 0, j = 0;
	
	while (i < a.length() && j < b.length()) {
		if (a[i] != b[j] && a[i] != ' ' && b[j] != ' ')
			return false;
		else if (a[i] == b[j]) {
			i++;
			j++;
		}
		
		if (b[j] == ' ')
			j++;
		
		if (a[i] == ' ')
			i++;
	}
	
	return true;
}

int main () {
	int limite = 0;
	bool ignore = false;
	Language language;
	
	limpiar;
	
	string file1Re = "", file2Re = "";
	
	while (true) {
		cout << language.introduce;
		
		string file1, file2;
		cin >> file1;
		if (file1[0] != '\\' || file1 == "\\re" || file1 == "\\repeat") {
			if (file1 != "\\re" && file1 != "\\repeat"){
				cin >> file2;
				file1Re = file1;
				file2Re = file2;
			} else if (file1Re != "" && file2Re != "") {
				file1 = file1Re;
				file2 = file2Re;
			}

			ifstream file1Input, file2Input;
			
			const char* Ruta1 = file1.c_str();
			const char* Ruta2 = file2.c_str();
			
			file1Input.open(Ruta1);
			file2Input.open(Ruta2);

			if (file1Input.is_open() && file2Input.is_open()) {
				int count = 1, fails = 0;
				
				// While both files do not reach End Of File and has not exceeded the limit errors (if limit = 0, no limit)
				while (!file1Input.eof() && !file2Input.eof() && !(limite != 0 && fails >= limite)) {
					string a,b;
					getline (file1Input, a);
					getline (file2Input, b);
					
					if (!ignore && a != b) {
						cout << language.difference << count << " ----//\n";
						cout << file1 << ": " << a << '\n';
						cout << file2 << ": " << b << "\n\n";
						fails++;
					} else if (ignore && !difEspIgnore (a,b)) { // Said something when the difference is only about spaces.
						cout << language.difference << count << " ----//\n";
						cout << file1 << ": " << a << '\n';
						cout << file2 << ": " << b << "\n\n";
						fails++;
					}
					count++;
				}
				
				// If the first input is bigger than the second
				if (file1Input.eof() && !file2Input.eof()) {
					cout << language.length_error1 << file1 << language.length_error2 << file2 << ".\n";
					cout << language.fails << fails << '\n';
				}
				// If the second input is bigger than the first
				else if (!file1Input.eof() && file2Input.eof()) {
					cout << language.length_error1 << file2 << language.length_error2 << file1 << ".\n";
					cout << language.fails << fails << '\n';
				}
				else if (fails == 0){
					cout << language.same;
				} else if (fails >= limite && limite != 0) {
					cout << language.limit_errors << fails << ").\n";
				} else {
					cout << language.fails << fails << '\n';
				}
				
				file1Input.close();
				file2Input.close();
			}
			else {
				cout << language.files_not_found;
			}
			
			cin.sync();
			cout << language.continue_;
			
			string aux;
			cin >> aux;
			if (aux == "n")
				return 0;
				
			limpiar;
		}
		else {
			// If we are using some commands
			if (file1 == "\\limit" || file1 == "\\l") {
				cin >> limite;
				if (!cin) {
					cin.clear(); // clear the "fail" condition
					while (cin.get() != '\n'); // get rid of everything in the input buffer
					limite = 0;
				}
				if (limite < 0)
					limite = 0;
				
				limpiar;
				cout << "Limite = " << limite << '\n';
			} else if (file1 == "\\help" || file1 == "\\h") {
				cout << language.commands;
			} else if (file1 == "\\ignore" || file1 == "\\i") {
				string ignorando;
				cin >> ignorando;
				ignore = (ignorando == "true" || ignorando == "t" || ignorando == "1");
				limpiar;
				cout << "Ignore = " << (ignore?"True":"False") << '\n';
			} else if (file1 == "\\exit" || file1 == "\\e") {
				return 0;
			} else if (file1 == "\\credits" || file1 == "\\c") {
				limpiar;
				cout << language.credits;
			}else if (file1 == "\\language" || file1 == "\\la") {
				string aux;
				cin >> aux;
				language.changeLanguage (aux);
			} else {
				limpiar;
				cout << language.unknown;
			}
			cout << '\n';
		}
	}
	
	return 0;
}