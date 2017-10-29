#ifndef RIQ_H
#define RIQ_H


class Riq
{
    public:
        Riq();
        virtual ~Riq();
        bool parseVar(char** buf);
        bool parseArray(char** buf);
        void dumpArray(char** buf, unsigned int bytes, unsigned int items, unsigned short itemsOnLine);
        void dumpTimeStamp(char** buf, const char* msg);
    protected:
    private:
};

#endif // RIQ_H
