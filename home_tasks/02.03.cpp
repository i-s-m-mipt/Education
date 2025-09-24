#include <iostream>

// int main() {
//     char symb = 'a';
//     std::cin >> symb;

//     // int num_ascii = static_cast<int>(symb);

//     switch (symb) {

//         // Uppercase
//         case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
//         case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
//         case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
//         case 'V': case 'W': case 'X': case 'Y': case 'Z':
//             std::cout << "Uppercase" << std::endl;
//             break;

//         // Lowercase
//         case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
//         case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
//         case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
//         case 'v': case 'w': case 'x': case 'y': case 'z':
//             std::cout << "Lowercase" << std::endl;
//             break;

//         // Digits
//         case '0': case '1': case '2': case '3': case '4': case '5': case '6':
//         case '7': case '8': case '9':
//             std::cout << "Digits" << std::endl;
//             break;

//         // Punctuation marks
//         case ' ': case '!': case '#': case '$': case '%': case '&': case '(':
//         case ')': case '[': case ']': case '*': case '+': case ',': case '-':
//         case '.': case '/': case ':': case ';': case '<': case '>': case '=':
//         case '?': case '@': case '|': case '{': case '}': case '^': case '~':
//         case '"': case '_':
//             std::cout << "Punctuation marks" << std::endl;
//             break;

//         default:
//             std::cout << "Others symbols" << std::endl;
//             break;

//     }

//     return 0;
// }

int main() {
  char symb = 'a';
  std::cin >> symb;

  // int num_ascii = static_cast<int>(symb);

  switch (symb) {

  // Uppercase
  case 'A' ... 'Z':
    std::cout << "Uppercase" << std::endl;
    break;

  // Lowercase
  case 'a' ... 'z':
    std::cout << "Lowercase" << std::endl;
    break;

  // Digits
  case '0' ... '9':
    std::cout << "Digits" << std::endl;
    break;

  // Punctuation marks
  case ' ':
  case '!':
  case '#':
  case '$':
  case '%':
  case '&':
  case '(':
  case ')':
  case '[':
  case ']':
  case '*':
  case '+':
  case ',':
  case '-':
  case '.':
  case '/':
  case ':':
  case ';':
  case '<':
  case '>':
  case '=':
  case '?':
  case '@':
  case '|':
  case '{':
  case '}':
  case '^':
  case '~':
  case '"':
  case '_':
    std::cout << "Punctuation marks" << std::endl;
    break;

  default:
    std::cout << "Others symbols" << std::endl;
    break;
  }

  return 0;
}