��    /      �  C           C     9   ]  o   �  B     m   J  ?   �  \   �  ;   U  P   �  [   �     >  @   A  N   �  J   �  D     d   a  �   �  :   a	     �	     �	     �	  0   �	     �	  5   
  	   ;
     E
  �   Z
  )   "  "   L  1   o  +   �  &   �  A   �  ;   6     r  /   �  7   �  3   �  :     ;   Y  $   �     �     �     �       2     �  G  �   &  r   �  �   -  �   �  �   v  j     �   �  d     �   l  �        �  o   �  �     �   �  w     �   �    E  a   [  ,   �     �  8   �  ^   ,     �  T   �  (      *   )  �  T  ^   �  N   :  W   �  �   �  0   �  t   �  h   S     �  m   �  �   =   �   �   �   E!  �   �!  G   j"  =   �"  ?   �"     0#     D#  s   Z#           -                	   .          '                 
   !   ,   +                   )          &               #                         "           /                            %                           $      *   (                 --byte-subst=FORMATSTRING   substitution for unconvertible bytes
   --help                      display this help and exit
   --unicode-subst=FORMATSTRING
                              substitution for unconvertible Unicode characters
   --version                   output version information and exit
   --widechar-subst=FORMATSTRING
                              substitution for unconvertible wide characters
   -c                          discard unconvertible characters
   -f ENCODING, --from-code=ENCODING
                              the encoding of the input
   -l, --list                  list the supported encodings
   -s, --silent                suppress error messages about conversion problems
   -t ENCODING, --to-code=ENCODING
                              the encoding of the output
 %s %s argument: A format directive with a size is not allowed here. %s argument: A format directive with a variable precision is not allowed here. %s argument: A format directive with a variable width is not allowed here. %s argument: The character '%c' is not a valid conversion specifier. %s argument: The character that terminates the format directive is not a valid conversion specifier. %s argument: The format string consumes more than one argument: %u argument. %s argument: The format string consumes more than one argument: %u arguments. %s argument: The string ends in the middle of a directive. %s: I/O error %s:%u:%u %s:%u:%u: cannot convert %s:%u:%u: incomplete character or shift sequence (stdin) Converts text from one encoding to another encoding.
 I/O error Informative output:
 License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 Options controlling conversion problems:
 Options controlling error output:
 Options controlling the input and output format:
 Report bugs to <bug-gnu-libiconv@gnu.org>.
 Try '%s --help' for more information.
 Usage: %s [OPTION...] [-f ENCODING] [-t ENCODING] [INPUTFILE...]
 Usage: iconv [-c] [-s] [-f fromcode] [-t tocode] [file ...] Written by %s.
 cannot convert byte substitution to Unicode: %s cannot convert byte substitution to target encoding: %s cannot convert byte substitution to wide string: %s cannot convert unicode substitution to target encoding: %s cannot convert widechar substitution to target encoding: %s conversion from %s to %s unsupported conversion from %s unsupported conversion to %s unsupported or:    %s -l
 or:    iconv -l try '%s -l' to get the list of supported encodings Project-Id-Version: libiconv 1.15-pre1
Report-Msgid-Bugs-To: bug-gnu-libiconv@gnu.org
POT-Creation-Date: 2016-12-04 17:16+0100
PO-Revision-Date: 2016-12-12 23:42+0200
Last-Translator: Roumen Petrov <transl@roumenpetrov.info>
Language-Team: Bulgarian <dict@ludost.net>
Language: bg
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Bugs: Report translation errors to the Language-Team address.
Plural-Forms: nplurals=2; plural=(n != 1);
   --byte-subst=ФОРМАТИРАЩ_НИЗ
                              заместител на непреобразуваеми байтове
   --help                      показване на тази помощ и изход от програмата
   --unicode-subst=ФОРМАТИРАЩ_НИЗ
                              заместител на непреобразуваеми знаци от Уникод
   --version                   извеждане на сведение за версията и изход от
                              програмата
   --widechar-subst=ФОРМАТИРАЩ_НИЗ
                              заместител на непреобразуваеми широки знаци
   -c                          пренебрегване на непреобразуваеми знаци
   -f КОДИРАНЕ, --from-code=КОДИРАНЕ
                              кодиране на входните данни
   -l, --list                  изброяване на поддържаните кодирания
   -s, --silent                подтискане на съобщенията за грешки при
                              преобразуване
   -t КОДИРАНЕ, --to-code=КОДИРАНЕ
                              кодиране на изходните данни
 %s %s аргумент: не е позволена директива за форматиране с размер. %s аргумент: не е позволена директива за форматиране с променлива точност. %s аргумент: не е позволена директива за форматиране с променлива ширина. %s аргумент: знакът '%c' не е правилен определител за преобразуване. %s аргумент: знакът, завършващ директивата за форматиране, не е правилен определител за преобразуване. %s аргумент: форматиращият низ използва повече от един аргумент: %u аргумент. %s аргумент: форматиращият низ използва повече от един аргумент: %u аргумента. %s аргумент: низът завършва по средата на директивата. %s: входно/изходна грешка %s:%u:%u %s:%u:%u: не може да се преобразува %s:%u:%u: непълен знак или изместваща последователност (стандартен вход) Преобразува текст от едно кодиране към друго.
 входно/изходна грешка Извеждане на сведение:
 Разрешително GPLv3+: Версия 3 на GNU GPL или следваща <http://gnu.org/licenses/gpl.html>
Това е свободен програмен продукт: свободни сте да го променяте и разпространя-
вате.  Не се дават НИКАКВИ ГАРАНЦИИ до степента позволена от закона.
 Аргументи управляващи проблеми при преобразуване:
 Аргументи задаващи извеждането на грешки:
 Аргументи задаващи входния и изходния формати:
 Подавайте доклади за грешки в програмата на <bug-gnu-libiconv@gnu.org>.
Подавайте доклади за грешки в превода на <dict@ludost.net>.
 За повече сведения '%s --help'.
 Употреба: %s [АРГУМЕНТИ...] [-f КОДИРАНЕ] [-t КОДИРАНЕ] [ВХОДЕН_ФАЙЛ...]
 Употреба: iconv [-c] [-s] [-f от_кодиране] [-t към_кодиране] [файл ...] Автори: %s.
 заместителят за байт към Уникод не може да се преобразува: %s заместителят за байт не може да се преобразува в резултатното кодиране: %s заместителят за байт в Уникод не може да се преобразува в широк знак: %s заместителят за Уникод не може да се преобразува към резултатното кодиране: %s заместителят за широк знак не може да се преобразува към резултатното кодиране: %s не се поддържа преобразуване от %s към %s не се поддържа преобразуване от %s не се поддържа преобразуване към %s или:      %s -l
 или:      iconv -l опитайте с '%s -l', за да получите списък с поддържаните кодирания 