#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <limits>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fcntl.h>
#include <algorithm>
using namespace std;
void Menu(int &tries);
void GetAndCheckInput(const wstring &CorrectWord, wstring &guess);
void CheckGuess(const wstring &guess, const wstring &CorrectWord);
wstring RandomWordSelection(const string &filename);
HANDLE hConsole; // windows API
vector<wstring> wordlist;
map<wchar_t, int> ColourOfLetters; // gia xrwmata pliktrologiou

int main()
{
  srand(time(0));
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  setlocale(LC_ALL, "el_GR.UTF-8");

  int PlayAgain = 1;

  SetConsoleTextAttribute(hConsole, 8);
  wcout << L"(Γράψε ? για οδηγίες)" << endl;
  SetConsoleTextAttribute(hConsole, 15);

  while (PlayAgain)
  {
    for (wchar_t c : L"ΕΡΤΥΘΙΟΠΑΣΔΦΓΗΞΚΛΖΧΨΩΒΝΜ")
    {
      ColourOfLetters[c] = 15;
    }

    int tries = 1;

    SetConsoleTextAttribute(hConsole, 11);
    cout << R"(
   
  ██╗    ██╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗
  ██║    ██║██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝
  ██║ █╗ ██║██║   ██║██████╔╝██║  ██║██║     █████╗  
  ██║███╗██║██║   ██║██╔══██╗██║  ██║██║     ██╔══╝  
  ╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝███████╗███████╗
   ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
                                                                                                  
   )" << endl;
    SetConsoleTextAttribute(hConsole, 15);

    wstring CorrectWord = RandomWordSelection("5letterwords.txt"), guess;

    while (true)
    {
      Menu(tries);
      SetConsoleTextAttribute(hConsole, 5);
      cout << "\nΠΡΟΣΠΑΘΕΙΑ : " << tries << endl;
      SetConsoleTextAttribute(hConsole, 15);
      GetAndCheckInput(CorrectWord, guess);
      CheckGuess(guess, CorrectWord);

      if (guess == CorrectWord)
      {
        SetConsoleTextAttribute(hConsole, 10);
        wcout << L"\n===================";
        wcout << L"\nΜΠΡΑΒΟ! ΤΗΝ ΒΡΗΚΕΣ!" << endl;
        wcout << L"===================\n";
        break;
      }

      tries++;
      if (tries == 7)
      {
        SetConsoleTextAttribute(hConsole, 12);
        wcout << L"\n===================================\n";
        wcout << L"ΔΥΣΤΥΧΩΣ ΕΧΑΣΕΣ! Η ΛΕΞΗ ΗΤΑΝ: " << CorrectWord << endl;
        wcout << L"===================================\n";
        break;
      }
    }

    _setmode(_fileno(stdin), _O_TEXT);
    while (true)
    {
      SetConsoleTextAttribute(hConsole, 15);
      wcout << L"\nΘΑ ΗΘΕΛΕΣ ΝΑ ΠΡΟΣΠΑΘΗΣΕΙΣ ΞΑΝΑ; (1 -> ΝΑΙ / 0 -> ΟΧΙ) : ";

      if (cin >> PlayAgain && (PlayAgain == 0 || PlayAgain == 1))
      {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        break;
      }
      else
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // gia na min pernei to enter ws eisodo
        SetConsoleTextAttribute(hConsole, 12);
        wcout << L"\nΛΑΝΘΑΣΜΕΝΗ ΑΠΑΝΤΗΣΗ! ΠΑΡΑΚΑΛΩ ΓΡΑΨΕ 1 ΓΙΑ ΝΑΙ / ΚΑΙ 0 ΓΙΑ ΟΧΙ : ";
      }
    }
  }
}

void Menu(int &tries)
{
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  wstring qwerty = L"ΕΡΤΥΘΙΟΠΑΣΔΦΓΗΞΚΛΖΧΨΩΒΝΜ";
  SetConsoleTextAttribute(hConsole, 15);
  if (tries == 1)
    cout << "\t\t\t_ _ _ _ _" << endl;

  cout << endl;

  wcout << L"\t\t     ";
  for (int i = 0; i <= 7; i++)
  {
    SetConsoleTextAttribute(hConsole, ColourOfLetters[qwerty[i]]);
    wcout << qwerty[i] << L" ";
  }
  wcout << endl
        << "\t\t    ";

  for (int i = 8; i <= 16; i++)
  {
    SetConsoleTextAttribute(hConsole, ColourOfLetters[qwerty[i]]);
    wcout << qwerty[i] << L" ";
  }
  wcout << endl;

  wcout << L"\t\t      ";
  for (int i = 17; i <= 23; i++)
  {
    SetConsoleTextAttribute(hConsole, ColourOfLetters[qwerty[i]]);
    wcout << qwerty[i] << L" ";
  }
  wcout << endl
        << endl;
}

wstring RandomWordSelection(const string &filename)
{ // const gia na min exoume allages sto filename kai & gia apodosi
  wifstream file(filename);
  wstring word;

  while (getline(file, word))
  {
    if (!word.empty())
    {                           // elegxos gia kenh seira sto txt
      wordlist.push_back(word); // vazei sto vector tis lexeis tou txt
    }
  }

  int selectedword = rand() % wordlist.size();
  return wordlist[selectedword];
}

int isWord(const wstring &guess)
{

  for (wchar_t character : guess)
  {
    if (!iswalpha(character) || !((character >= 0x0370 && character <= 0x03FF) || (character >= 0x1F00 && character <= 0x1FFF))) // elegxos gia mono ellinika grammata
    {
      return 0;
    }
  }
  return 1;
}
void GetAndCheckInput(const wstring &CorrectWord, wstring &guess)
{
  _setmode(_fileno(stdin), _O_U16TEXT); // utf 16 gia thn eisodo tou xrhsth sta ellinika

  while (true)
  {

    wcout << L"ΓΡΑΨΕ ΜΙΑ ΕΛΛΗΝΙΚΗ ΛΕΞΗ 5 ΓΡΑΜΜΑΤΩΝ: ";
    getline(wcin, guess);
    guess.erase(remove(guess.begin(), guess.end(), L' '), guess.end());
    wcout << endl;

    for (wchar_t &character : guess)
    {
      character = towupper(character);
      switch (character)
      {

      case L'Ά':
        character = L'Α';
        break;
      case L'Έ':
        character = L'Ε';
        break;
      case L'Ή':
        character = L'Η';
        break;
      case L'Ί':
        character = L'Ι';
        break;
      case L'Ό':
        character = L'Ο';
        break;
      case L'Ύ':
        character = L'Υ';
        break;
      case L'Ώ':
        character = L'Ω';
        break;
      case L'ς':
        character = L'Σ';
        break;
      }
    }

    if (guess == L"?")
    {
      SetConsoleTextAttribute(hConsole, 11);
      wcout << L"\n-------- ΟΔΗΓΙΕΣ --------" << endl;
      wcout << L"\nΣτόχος : Πρέπει να βρεις μια λέξη 5 γραμμάτων.\n" << endl;
      wcout << L"Χρώματα:\n  Πράσινο: σωστό γράμμα στη σωστή θέση\n  Κίτρινο: σωστό γράμμα αλλά λάθος θέση\n  Γκρι: το γράμμα δεν υπάρχει στη λέξη.\n"
            << endl;
      SetConsoleTextAttribute(hConsole, 15);
      continue;
    }

    if (guess.length() != 5 || !isWord(guess))
    {
      SetConsoleTextAttribute(hConsole, 4);
      wcout << L"ΜΗ ΕΚΓΥΡΗ ΑΠΑΝΤΗΣΗ. ΠΑΡΑΚΑΛΩ ΓΡΑΨΕ ΜΙΑ ΕΛΛΗΝΙΚΗ ΛΕΞΗ 5 ΓΡΑΜΜΑΤΩΝ" << endl;
      SetConsoleTextAttribute(hConsole, 15);
      continue;
    }

    int wordExists = 0;
    for (const wstring &word : wordlist) // elegxei to txt gia na doume an o xristis exei valei lexi pou iparxei
    {
      if (word == guess)
      {
        wordExists = 1;
        break;
      }
    }

    if (!wordExists)
    {
      SetConsoleTextAttribute(hConsole, 4);
      wcout << L"Η ΛΕΞΗ ΑΥΤΗ ΔΕΝ ΥΠΑΡΧΕΙ. ΞΑΝΑΔΟΚΙΜΑΣΕ!" << endl;
      SetConsoleTextAttribute(hConsole, 15);
      continue;
    }

    break;
  }
}

void CheckGuess(const wstring &guess, const wstring &CorrectWord)
{
  int colour[5] = {15, 15, 15, 15, 15}; // ola aspra
  int matched[5] = {0};

  for (int i = 0; i < 5; i++)
  {
    if (guess[i] == CorrectWord[i])
    {
      colour[i] = 10; // prasino
      matched[i] = 1; // einai sthn thesi pou prepei
    }
  }

  for (int i = 0; i < 5; i++)
  {
    if (colour[i] == 10)
      continue;

    for (int j = 0; j < 5; j++)
    {
      if (guess[i] == CorrectWord[j] && !matched[j] && guess[j] != CorrectWord[j])
      {
        colour[i] = 6;  // kitrino
        matched[j] = 1; // an iparxei kapou allou
        break;
      }
    }
  }

  cout << "\t\t\t";
  for (int i = 0; i < 5; i++)
  {
    if (colour[i] == 15)
    {
      SetConsoleTextAttribute(hConsole, colour[i]);
      cout << "_" << " ";
      ColourOfLetters[guess[i]] = 8; // gkri gia grammata poy den iparxoyn
    }
    else
    {
      SetConsoleTextAttribute(hConsole, colour[i]);
      wcout << guess[i] << " ";
      if (ColourOfLetters[guess[i]] == 10)
        continue; // idi prasino ara min kaneis allo xrwma sto pliktrologio
      if (ColourOfLetters[guess[i]] == 6 && colour[i] == 8)
        continue;                            // idio gia kitrino gia na min iparxoun downgrades
      ColourOfLetters[guess[i]] = colour[i]; // ipoloipa xrwmata gia pliktrologio
    }
  }
  SetConsoleTextAttribute(hConsole, 15);
  wcout << endl;
}
