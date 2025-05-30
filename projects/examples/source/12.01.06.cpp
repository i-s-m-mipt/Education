//////////////////////////////////////////////////////

#include <string>
#include <unordered_map>

//////////////////////////////////////////////////////

int main()
{
    std::unordered_map < char32_t, std::string > map =
    { 
        { U'А', "A"   }, { U'а', "a"   },
        { U'Б', "B"   }, { U'б', "b"   },
        { U'В', "V"   }, { U'в', "v"   },
        { U'Г', "G"   }, { U'г', "g"   },
        { U'Д', "D"   }, { U'д', "d"   },
        { U'Е', "E"   }, { U'е', "e"   },
        { U'Ё', "Yo"  }, { U'ё', "yo"  },
        { U'Ж', "Zh"  }, { U'ж', "zh"  },
        { U'З', "Z"   }, { U'з', "z"   },
        { U'И', "I"   }, { U'и', "i"   },
        { U'Й', "J"   }, { U'й', "j"   },
        { U'К', "K"   }, { U'к', "k"   },
        { U'Л', "L"   }, { U'л', "l"   },
        { U'М', "M"   }, { U'м', "m"   },
        { U'Н', "N"   }, { U'н', "n"   },
        { U'О', "O"   }, { U'о', "o"   },
        { U'П', "P"   }, { U'п', "p"   },
        { U'Р', "R"   }, { U'р', "r"   },
        { U'С', "S"   }, { U'с', "s"   },
        { U'Т', "T"   }, { U'т', "t"   },
        { U'У', "U"   }, { U'у', "u"   },
        { U'Ф', "Ph"  }, { U'ф', "ph"  },
        { U'Х', "H"   }, { U'х', "h"   },
        { U'Ц', "Ts"  }, { U'ц', "ts"  },
        { U'Ч', "Ch"  }, { U'ч', "ch"  },
        { U'Ш', "Sh"  }, { U'ш', "sh"  },
        { U'Щ', "Sch" }, { U'щ', "sch" },
        { U'Ы', "I"   }, { U'ы', "i"   },
        { U'ъ', ""    }, { U'ь', "'"   },
        { U'Э', "E"   }, { U'э', "e"   },
        { U'Ю', "Yu"  }, { U'ю', "yu"  },
        { U'Я', "Ya"  }, { U'я', "ya"  } 
    };
}

//////////////////////////////////////////////////////