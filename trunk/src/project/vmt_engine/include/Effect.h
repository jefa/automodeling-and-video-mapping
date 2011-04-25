#ifndef EFFECT_H
#define EFFECT_H

enum EFFECT_TYPES {
	FADE_EFFECT,
	POSITION_EFFECT,
	TEXTURE_EFFECT
};

class Effect
{
    public:
        Effect();
        virtual ~Effect();

        virtual void play() = 0;
        virtual void test() = 0;
        virtual int getType() = 0;
    protected:
    private:
};

#endif // EFFECT_H
