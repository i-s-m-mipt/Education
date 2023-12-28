#include <iostream>

class Compression
{
public:

    virtual ~Compression() = default;

    virtual void compress() const = 0;

}; // class Compression

class ZIP_Compression : public Compression
{
public:

    void compress() const override 
    { 
        std::cout << "ZIP compression" << std::endl; 
    }

}; // class ZIP_Compression : public Compression

class RAR_Compression : public Compression
{
public:

    void compress() const override 
    { 
        std::cout << "RAR compression" << std::endl; 
    }

}; // class RAR_Compression : public Compression

class ARJ_Compression : public Compression
{
public:

    void compress() const override 
    { 
        std::cout << "ARJ compression" << std::endl; 
    }

}; // class ARJ_Compression : public Compression

class Compressor
{
public:

    explicit Compressor(Compression * compression) : m_compression(compression) 
    {
        if (!m_compression) // good: verify if nullptr
        {
            std::cout << "invalid compression" << std::endl;
        }
    }

    ~Compressor() { delete m_compression; } // good: no memory leak

public:

    void compress() const { m_compression->compress(); }

private:
    
    Compression * m_compression;

}; // class Compressor

int main()
{
    Compressor(new ZIP_Compression).compress(); // note: choose algorithm

    return 0;
}