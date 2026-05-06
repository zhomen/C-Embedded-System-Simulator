class IDevice 
{
public:
    virtual void tick() = 0;
    virtual void write_register(int addr, int value) = 0;
    virtual int read_register(int addr) = 0;
};