#ifndef ABSTRACTMTRX_H
#define ABSTRACTMTRX_H

class AbstractMtrx
{
public:
    AbstractMtrx();
    virtual ~AbstractMtrx() = 0;

    virtual bool isEmpty() const noexcept;
    virtual int getSize() const noexcept;
    virtual int getWidth() const noexcept;
    virtual int getHeight() const noexcept;
    virtual int elemsNum() const noexcept;

    virtual void reset() noexcept = 0;

protected:
    virtual void alloc_data() = 0;

protected:
    int width = -1;
    int height = -1;
    int size = -1;
    int elems_num = -1;
};

#endif // ABSTRACTMTRX_H
