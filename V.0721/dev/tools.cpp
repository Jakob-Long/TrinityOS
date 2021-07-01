extern "C" int strCall(char *);

class DevTools {
    public:
        int strLen(char *usr);

        char MSG = '!';
        int len;
        char conv;
        char strConv[5];
};

int DevTools::strLen(char *usr) {
    while ( usr[len] != '\0' ) {
        len++;
    }

    // Due to the loop above, I cannot declare len as anything.
    // I will get this bug fixed in a bit by trying to return out
    // of the loop and then declaring len.
    //if ( len >= 10 ) errorPop();

    conv = len + '0';
    strConv[0] = conv;

    return len;
}

int strCall(char *inp) {
    //DevTools cmd;
    //int sout = cmd.strLen(inp);
    //return sout;
}