
<HTML>
<HEAD>
<TITLE>Homework #4 - CSCI 531, Spring 2015</TITLE>
<LINK HREF="../../cs531bc.css" REL="stylesheet" TYPE="text/css">
<LINK REV="made" HREF="mailto:bill.cheng@acm.org"></HEAD>
<BODY BGCOLOR="#FFFFFF" LINK="#D02090" VLINK="#996600" ALINK="#990000">

<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0 WIDTH=100%>
<TR>
<TD ALIGN=LEFT VALIGN=TOP>
<!-- COL 3, every page should be different -->

<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
<FONT COLOR="#ffffff"><A
NAME="intro"><B>Assignment</B></A></FONT>
</TD>
</TR>

<TR><TD COLSPAN=3 ALIGN=LEFT>
The purpose of this assignment is to get familiar with
a classical polyalphabetic substitution cipher and the
cryptanalysis of it.

<P>

</TD>
</TR>
<TR><TD>&nbsp;</TD></TR>

<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
<FONT COLOR="#ffffff"><A
NAME="compile"><B>Compiling</B></A></FONT>
</TD>
</TR>

<TR><TD COLSPAN=3 ALIGN=LEFT>

<PRE>
make hw4</PRE>
an executable named <B>hw4</B> is created.

</TD>
</TR>
<TR><TD>&nbsp;</TD></TR>

<TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
<FONT COLOR="#ffffff"><A
NAME="syntax"><B>Commandline Syntax & Program
Output</B></A></FONT>
</TD>
</TR>
<TR><TD COLSPAN=3 ALIGN=LEFT>
The commandline syntax for <B>hw4</B> is as follows:

<PRE>
    <B>hw4</B> <B>keygen</B> <B>-p=</B>pphrase <B>-t=</B>period
    <B>hw4</B> <B>crypt</B> <B>-k=</B>keyfile [file]
    <B>hw4</B> <B>invkey</B> keyfile
    <B>hw4</B> <B>histo</B> <B>-t=</B>period <B>-i=</B>which [file]
    <B>hw4</B> <B>solve</B> <B>-l=</B>max_t file</PRE>

<P>

Square bracketed items are optional.
Follows the UNIX convention that <B>commandline options</B>
can come in any order.  (Note: a <B>commandline option</B> is a
commandline argument that begins with a <B>-</B> character in a
commandline syntax specification.)
If an input file is not specified, the program should
read from <TT>stdin</TT>.
Output of the program must go to <TT>stdout</TT> and
error messages must go to <TT>stderr</TT>.

<P>

The meaning of the commands are:

<BLOCKQUOTE>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>keygen</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Generate a <A HREF="#keyfile">keyfile</A> with a specified <TT>period</TT>
                       to be used by the
                       <A HREF="#vigenere">full Vigen&#232;re cipher</A>
                       (with polyalphabetic substitution).
                       The ASCII string <TT>pphrase</TT>
                       contains the passphrase (which must not be empty) for
                       <A HREF="#shuffle">key generation</A>
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>crypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Encrypts (or decrypts) an input ASCII text file with
                       the keys specified in <TT>keyfile</TT>.
                       The output is an ASCII text file encrypted (or decrypted)
                       using a <A HREF="#vigenere">full Vigen&#232;re cipher</A>
                       (with polyalphabetic substitution).
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>invkey</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Create an inverse permutation key file from
                       <TT>keyfile</TT>.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>histo</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Produce a histogram of ciphertext character frequencies
                       assuming the ciphertext is produced by a
                       polyalphabetic substitution cipher with period
                       equals <TT>period</TT>.  <TT>which</TT> specifies
                       a one-based index for the alphabets.  The output
                       must be sorted according to the frequencies of the
                       ciphertext characters in descending order.
                       Please do not
                       consider any characters that is not a lowercase English
                       character (i.e., between <TT>'a'</TT> and <TT>'z'</TT>,
                       inclusive).
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>solve</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>Apply the Method of Kasiski and use Index of Coincidence
                       in order to determine the period of a ciphertext
                       encrypted by a
                       <A HREF="#vigenere">full Vigen&#232;re cipher</A>
                       (with polyalphabetic substitution).
        </TD>
    </TR>
</TABLE>
</BLOCKQUOTE>

<P>

The output for various commands are as follows.

<BLOCKQUOTE>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>keygen</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            You must use the <A HREF="#shuffle">Random Permutation</A>
            algorithm to generate the key file.
            The output of this command is a key file in the format
            suitable to be used by the
            <A HREF="#vigenere">full Vigen&#232;re cipher</A>
            (with polyalphabetic substitution).
            The number of lines in the output must be exactly equal to
            the specified <TT>period</TT>.  Each line is
            exactly 26 characters long (lowercase English characters)
            and is terminated with a <TT>'\n'</TT> character.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>crypt</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The output of this command is an ASCII text file.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>invkey</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The output of this command is a key file in the format
            identical to that of the input key file.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>histo</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            The output of this command is a histogram of ciphertext
            character frequencies.  The output must be sorted according
            to the frequencies of the ciphertext characters in descending order.
            If there is a tie, you must output letters earlier in the alphabet
            first.
            You should first print out the total number of lowercase
            English ciphertext character (L).  Then for the most frequently
            occurred ciphertext character, print the number of occurrences
            followed by the corresponding frequency in percentages.
            For example,
            if <TT>'y'</TT> occurs most frequencly with a count of 12 and
            <TT>L</TT> is 76, you should output
            (without leading space characters):
    <PRE>
    y: 12 (15.79%)</PRE>
            The percentages must have exactly 2 digits after the decimal point.
        </TD>
    </TR>
    <TR><TD>&nbsp;</TD></TR>
    <TR><TD ALIGN=LEFT VALIGN=TOP><B>solve</B></TD>
        <TD VALIGN=TOP>&nbsp;&nbsp;:&nbsp;&nbsp;</TD>
        <TD VALIGN=TOP>
            For this command, the output has 3 sections.
            The first section is related to the method of Kasiski.
            The 2nd section is related to the average index of coincidence.
            The 3rd section is related to the auto-correlation method.
            The output of each section with a banner indicating the method
            that is being used.
            Please see the <A HREF="#testdata">test data</A>
            section for the exact text.
            <P>
            For the Kasiski method, you should begin with a string
            length of 4 and outputs all ciphertext matches.
            (A string must only contain letters in the alphabet.)
            You should
            stop when no more matches can be found.  For a given
            string length, each line in the output corresponds to a match
            of two strings in the ciphertext. For example, if the first
            string starts at character index 123,
            the second string starts at character index 367,
            the strlength is 4, and the string is <TT>"uoez"</TT>,
            you should output (without leading space characters):
    <PRE>
    len=4, i=123, j=367, j-i=244, uoez</PRE>
            If at length 7, you do not found any matches, you should print
            (without leading space characters):
    <PRE>
    len=7, no more matches</PRE>
            and move on to the average index of coincidence method.
            Please note that the indices <TT>i</TT> and <TT>j</TT>
            are zero-based indices, i.e., the index for the first character
            in the file is zero.
            <P>
            For the average index of coincidence, you should compute
            the frequencies of the ciphertext characters and the
            index of coincidence (equation 7.2 on page 249 of the
            textbook,
            with <I>k<SUB>p</SUB></I>=0.0658).
            Then you should tabulate the expected
            index of coincidences for cycle lengths from 1 to <TT>max_t</TT>.
            You should print out the total number of lowercase
            English ciphertext character (L), the number of occurrences
            of each of the lowercase English ciphertext characters,
            the computed IC, and the expected ICs.
            Below is an example with <TT>max_t</TT> equaling 10.
    <PRE>
    L=346
    f('a')=7
    f('b')=14
    ...
    f('z')=20
    IC=0.041417442
    t=1, E(IC)=0.0658
    t=2, E(IC)=0.052091148
    ...
    t=10, E(IC)=0.041124067</PRE>
            <P>
            For the auto-correlation method
            (please see example 7.77 on page 250 of the textbook),
            for each possible period
            <I>T</I>
            (from 1 to <TT>max_t</TT>),
            you should count the total number of occurrences where
            the <I>i</I><SUP>&nbsp;th</SUP>
            ciphertext character is identical to
            the <I>(i+T)</I><SUP>&nbsp;th</SUP>
            ciphertext character, for <I>i</I> from 1 to <I>L-T</I>,
            where L is the length of the ciphertext and both
            ciphertext characters must be lowercase English characters.
            For example, if <I>T</I is 5 and the number of coincidence
            is 21, you should output (without leading space characters):
    <PRE>
    t=5, count=21</PRE>
        </TD>
    </TR>
</TABLE>
</BLOCKQUOTE>

            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A NAME="vigenere">
                <B>Full Vigen&#232;re Cipher</B></A></FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
In a full Vigen&#232;re cipher with period <I>T</I>,
<I>T</I> permutation functions are used.  Each permutation
function maps a single plaintext character to a ciphertext
character.  The <I>i</I><SUP>&nbsp;th</SUP> permutation
function maps the <I>i</I><SUP>&nbsp;th</SUP>,
<I>(i+T)</I><SUP>&nbsp;th</SUP>, <I>(i+2T)</I><SUP>&nbsp;th</SUP>, ...
plaintext characters to a ciphertext character.
Since we are dealing with lowercase ASCII characters
only, we can specify a permutation function with 26 lowercase
ASCII characters.  For example,
    <PRE>
    kybrcwsoxzlednhjfupitmvqag</PRE>

specifies that each characters in <TT>abcdefghijklmnopqrstuvwxyz</TT>
maps to <TT>kybrcwsoxzlednhjfupitmvqag</TT>, respectively.

<P>

<!--
  BC: need to say something about quitting if keyfile is bad
  BC: also need to add tests to the grading guidelines
  -->
<A NAME="keyfile">To</A> specify all <I>T</I> permutation functions, we
use a keyfile with <I>T</I> lines of text.  Each line is
26 characters long and is terminated with a <TT>'\n'</TT> character.
Furthermore, line <I>i</I> corresponds to the <I>i</I><SUP>&nbsp;th</SUP>
permutation function.
For example, a keyfile can look like the following (with <I>T</I>=5):
    <PRE>
    yvndjporftcualiwgxmzshqebk
    gqamiporzdtvynjlkbucfxswhe
    riacuysxzgwhvbnmjdklpqefot
    ldhwfjitrmpncazquxoeksvgyb
    gntyqmsjcoihpbadlwxvkezfru</PRE>

The rule of encryption is that if the <I>j</I><SUP>&nbsp;th</SUP>
input character is a lower case English character, it is encrypted
with the <I>(j mod T)</I><SUP>&nbsp;th</SUP> permutation function.
Otherwise, it is unencrypted.  If the plaintext is <TT>"ab@&nbsp;ab@"</TT>,
the ciphertext should be <TT>"yq@&nbsp;gv@"</TT> if the above keyfile is used for
encryption.

<P>

The above keyfile has the following inverse:
    <PRE>
    mykdxiqvoeznscgfwhujlbprat
    crtjzuayeoqpdngfbhwkslxvmi
    cndrwxjlbqstpoyuvagzemkhfi
    nzmbtexcgfuajlskpivhqwdryo
    onipvxalkhuqfbjmeygcztrsdw</PRE>

Using the above inverse keyfile to encrypt
<TT>"yq@&nbsp;gv@"</TT> will result in the original plaintext
<TT>"ab@&nbsp;ab@"</TT>.

<P>

For the purpose of this assignment, you may assume that the
original plaintext is a single line of ASCII text.  There is
only a single <TT>'\n'</TT> at the end of the line.  You may stop
reading the input as soon as you see a <TT>'\n'</TT> character.
If you encounter a character less than <TT>0x20</TT> or greater than <TT>0x7e</TT>
(except for <TT>'\n'</TT>), please abort your program and print an error message.
            </TD>
        </TR>
        <TR><TD>&nbsp;</TD></TR>
        <!-- Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT BGCOLOR="#000000" WIDTH=100%>
                <FONT COLOR="#ffffff"><A
                NAME="shuffle"><B>Random Permutation</B></A>
                    </FONT>
            </TD>
        </TR>
        <!-- Top Section -->
        <TR><TD COLSPAN=3 ALIGN=LEFT>
Given a list of N = 26 elements, please use the algorithm described
here to create a random permutation of the lower-case alphabet.

<P>

The algorithm is as follows:
   <PRE>
   state = "abcdefghijklmnopqrstuvwxyz";
   for itr = 1 to 2 do {
       L = 26
       while (L > 1) {
           X = RandomInteger()
           R = X % L
           if (R != L-1) {
               swap state[R] and state[L-1]
           }
           L = L - 1
       }
   }
   return state</PRE>

<A NAME="randominteger">Each call to the</A>
<TT>RandomInteger()</TT> function returns a random unsigned integer <TT>X</TT>
using the <A HREF="../hw2/#stream">simple stream cipher of HW2</A> as follows.
The <A HREF="../hw2/#stream">simple stream cipher of HW2</A> generates 8 bytes of random data
in each iteration.  You should treat each 8 bytes of data as two unsigned integers.
The first byte of the random data becomes the most-significant-byte of the first unsigned integer,
the 2nd byte of the random data becomes the 2nd most-significant-byte of the first unsigned integer,
the 3rd byte of the random data becomes the 3rd most-significant-byte of the first unsigned integer, and
the 4th byte of the random data becomes the least-significant-byte of the first unsigned integer.
The 5th byte of the random data becomes the most-significant-byte of the 2nd unsigned integer,
the 6th byte of the random data becomes the 2nd most-significant-byte of the 2nd unsigned integer,
the 7th byte of the random data becomes the 3rd most-significant-byte of the 2nd unsigned integer, and
finally, the 8th byte of the random data becomes the least-significant-byte of the 2nd unsigned integer.

<P>

For the <TT>keygen</TT> command, each "permutation" of the alphabet will consume 25 &times; 4 = 100 bytes of
output from the <A HREF="../hw2/#stream">simple stream cipher of HW2</A>.  This will give
you a line in the output key file.  When you proceed to the next line, please continue
to read 100 bytes of output from the simple stream cipher of HW2 <B>without resetting the
stream cipher</B>.

<P>

For example, if <TT>pphrase</TT> is <TT>"yesnomaybe"</TT>,
the first 8 bytes of our simple stream cipher output is <TT>cf686d0977103817</TT>.
Therefore, our first <TT>X = 0xcf686d09</TT>.
As a result, our first <TT>R = 0xcf686d09 % 26 = 1</TT>.  Therefore, you would
swap 'b' and 'z'.  Our 2nd <TT>X = 0x77103817</TT>.
As a result, our 2nd <TT>R = 0x77103817 % 25 = 14</TT>.  Therefore, you would
swap 'o' and 'y'.  For your debugging pleasure,
please checkout the your values for <TT>X</TT>, <TT>L</TT>, <TT>R</TT>, and <TT>state</TT>
when you run with <TT>-p=yesnomaybe -t=2</TT>
against <A HREF="keygen-debug.txt">this set of values and keys</A>.
            </TD>
        </TR>
        

</BODY>
</HTML>

