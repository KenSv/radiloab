#ifndef RIQ_H
#define RIQ_H


class Riq
{
    public:
        Riq();
        virtual ~Riq();
        bool parseVar(char** buf);
        bool parseArray(char** buf);
    protected:
    private:
};

#endif // RIQ_H
