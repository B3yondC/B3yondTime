#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H



class SystemInterface
{
public:

        enum class FullRefreshDirection
        {
                None,
                Left,
                Right,
                Up,
                Down
        };

        virtual void setFullRefreshDirection(FullRefreshDirection value) = 0;

        virtual ~SystemInterface();
};

#endif // SYSTEMINTERFACE_H
