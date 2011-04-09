#ifndef EFFECT_H
#define EFFECT_H


class Effect
{
    public:
        Effect();
        virtual ~Effect();

        virtual void play() = 0;
    protected:
    private:
};

#endif // EFFECT_H
