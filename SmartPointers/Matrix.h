
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<exception>

using namespace std;


class DIM_EXP : public exception
{
	virtual const char* what() const throw()
	{
		return "Dimension Mismatch Exception";
	}
} INVALID_DIMENTION_EXCEPTION;


class MyClass
{
public:
    int row;
	int col;
	float** array_;

    MyClass(int row, int col)
    {
        this->row = row;
        this->col = col;
        
        _crt_array_();
        
        _fil_rand();
        
    }
    
    MyClass(int row, int col, float crt_val)
    {
        this->row = row;
        this->col = col;
        
        _crt_array_(crt_val);
    }
    
    void Squaremat()
    {
        int r = 0;
        int c = 0;
        
        if(row	 >= col)
        {
            r = row;
            c = row;
        }
        else
        {
            r = col;
            c = col;
        }
        float** arr = new float*[r];
        for(int i = 0; i< r;++i)
        {
            arr[i] = new float[r];
        }
        for(int  i  = 0; i< r;++i)
            for(int j =0; j <r ; ++j)
            {
                arr[i][j] = 0;
            }
        
        for(int  i  = 0; i< row; ++i)
            for(int j =0; j <col ; ++j)
            {
                arr[i][j] = array_[i][j];
            }
        
        delete array_;
        
        array_ = arr;
        return ;
        
    }
    
    void print_array()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << array_[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }
    void Iterative_algo(int r1, int r2, int c1, int c2, MyClass* o)
    {
        for (int i = 0; r1 < r2; r1++, i++)
        {
            int _c1 = c1;
            for (int j = 0; _c1 < c2; _c1++, j++)
            {
                array_[i][j] = o->array_[r1][_c1];
            }
        }
        
    }
    
    
    void place(int r1, int re, int c1, int ce, MyClass& o)
    {
        for (int i = 0; r1 < re; r1++, i++)
        {
            int _c1 = c1;
            for (int j = 0; _c1 < ce; _c1++, j++)
            {
                array_[r1][_c1] = o.array_[i][j];
            }
        }
    }
    void operator=(MyClass* o)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array_[i][j] = o->array_[i][j];
            }
        }
    }
    bool operator==(MyClass& o)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (array_[i][j] != o.array_[i][j])
                    return false;
            }
        }
        return true;
    }
    MyClass* operator+(MyClass* o)
    {
        if (row != o->row || col != o->col)
            throw INVALID_DIMENTION_EXCEPTION;
        
        MyClass* r = new MyClass(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                r->array_[i][j] = array_[i][j] + o->array_[i][j];
            }
        }
        return r;
    }
    MyClass* operator*(MyClass& o)
    {
        if (col != o.row)
            throw INVALID_DIMENTION_EXCEPTION;
        
        MyClass *r = new MyClass(row, o.col);
        
        for (int i = 0; i < r->row; i++)
        {
            for (int j = 0; j < r->col; j++)
            {
                r->array_[i][j] = 0;
                for (int k = 0; k < col; k++)
                {
                    r->array_[i][j] += array_[i][k] * o.array_[k][j];
                }
            }
        }
        
        return r;
    }
    MyClass* StrassenAlgo(MyClass* o)
    {
        //Strassen Algorithim to multiply matrices
        //Takes an object pointer as input.
        
        if (col != o->row)
            //if number of columns of first is not equal to number of rows of second
            
            throw INVALID_DIMENTION_EXCEPTION;
        
        
        this->Squaremat();
        o->Squaremat();
        
        if (row == 2)
        {
            return (*this * *o);
        }
        else
        {
            int div_size = row / 2;
            int end = row;
            
            MyClass* r = new MyClass(row, col, 0);
            MyClass A11(div_size, div_size, 0);
            A11.Iterative_algo(0, div_size, 0, div_size, this);
            MyClass A12(div_size, div_size, 0);
            A12.Iterative_algo(0, div_size, div_size, end, this);
            MyClass A21(div_size, div_size, 0);
            A21.Iterative_algo(div_size, end, 0, div_size, this);
            MyClass A22(div_size, div_size, 0);
            A22.Iterative_algo(div_size, end, div_size, end, this);
            
            MyClass* B11 = new MyClass(div_size, div_size, 0);
            B11->Iterative_algo(0, div_size, 0, div_size, o);
            MyClass* B12 = new MyClass(div_size, div_size, 0);
            B12->Iterative_algo(0, div_size, div_size, end, o);
            MyClass* B21 = new MyClass(div_size, div_size, 0);
            B21->Iterative_algo(div_size, end, 0, div_size, o);
            MyClass* B22 = new MyClass(div_size, div_size, 0);
            B22->Iterative_algo(div_size, end, div_size, end, o);
            
            r->place(0, div_size, 0, div_size, *(*(A11.StrassenAlgo(B11)) + (A12.StrassenAlgo(B21))));
            r->place(0, div_size, div_size, end, *(*(A11.StrassenAlgo(B12)) + (A12.StrassenAlgo(B22))));
            r->place(div_size, end, 0, div_size, *(*(A21.StrassenAlgo(B11)) + (A22.StrassenAlgo(B21))));
            r->place(div_size, end, div_size, end, *(*(A21.StrassenAlgo(B12)) + (A22.StrassenAlgo(B22))));
            
            return r;
        }
    }
    
    ~MyClass()
    {
        //Delete all pointers in the destructor.
        for (int i = 0; i < row; i++)
        {
            delete[] array_[i];
        }
        delete array_;
    }
    
    private:
    void _crt_array_()
    {
        //Will create a new array with rows equal to rows and columns equal to columns
        
        array_ = new float*[row];
        for (int i = 0; i < row; i++)
        {
            array_[i] = new float[col];
        }
    }
    
    void _crt_array_(float crt_val)
    {
        //Will assign this value s crt_val to all elements of the array.
        
        array_ = new float*[row];
        for (int i = 0; i < row; i++)
        {
            array_[i] = new float[col];
            for (int j = 0; j < col; j++)
            {
                array_[i][j] = crt_val;
            }
        }
        
    }

    void _fil_rand()
    {
        srand(time(NULL));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                //Will generate random numbers from 1 to 10
                array_[i][j] = (rand() % 10)+1;
            }
        }
    }

};


