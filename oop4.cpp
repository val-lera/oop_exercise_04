/*Лабораторная работа №4
Выполнила: Блистунова Валерия
Группа М8О-201Б

Вариант №12: Трапеция, Ромб, 5-угольник
Разработать шаблоны классов согласно варианту задания.
Параметром шаблона должен являться скалярный тип данных, задающий тип данных для оси координат.
Классы должны иметь публичные поля. Фигуры являются фигурами вращения.
Для хранения координат фигур необходимо использовать шаблон std::pair.
Создать набор шаблонов, создающих функции, реализующие:
1. Вычисление геометрического центра фигуры;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры;
3. Вычисление площади фигуры;
Создать программу, которая позволяет:
Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
Вызывать для неё шаблонные функции функции (1-3 см. выше).*/

#include<iostream>
#include<cmath>
#include <type_traits>
#include <string>
#include <tuple>
#define pi 3.14159265358979323846
using namespace std;

template <class T>
double length(T a, T b, T c, T d){
        double l;
        using type=T;
        l= sqrt(pow((c-a),2)+pow((d-b),2));
        return l;
    };

template <class T>
class Trap{
    public:
    using type=T;
    using vertex=std::pair<T,T>;
    vertex a,b,c,d;
    Trap(){}
    Trap(vertex &v1, vertex &v2, vertex &v3){
        a=v1;
        b=v2;
        c=v3;
        vertex v4;
        v4.first= length(b.first, b.second, c.first, c.second)+2*length(a.first, a.second, b.first, a.second)+a.first;
        v4.second=a.second;
        d=v4;
        }
};

template <class T>
struct is_Trap{
    static const bool value = false;
};

template <class T>
struct is_Trap<Trap<T>>{
    static const bool value = true;
};

template <class T>
using Trap_coord = typename std::enable_if<is_Trap<T>::value, void >::type;

template <class T>
using Trap_area = typename std::enable_if<is_Trap<T>::value, typename T::type >::type;

template <class T>
using Trap_center = typename std::enable_if<is_Trap<T>::value, std::pair<typename T::type, typename T::type> >::type;

template <class T>
Trap_coord<T> print_coord(const T &t){
    cout << "Координаты вершин трапеции: ";
    cout << "(" << t.a.first << "; " << t.a.second << ")  ";
    cout << "(" << t.b.first << "; " << t.b.second << ")  "; 
    cout << "(" << t.c.first << "; " << t.c.second << ")  "; 
    cout << "(" << t.d.first << "; " << t.d.second << ")  " << endl;; 
}
template <class T>
std::pair<T, T> print_coord(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &f){
	std::pair<T,T> v1, v2, v3;
	v1 = std::get<0>(f);
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	Trap<T> t(v1, v2, v3);
	return print_coord(t);
}

template <class T>
Trap_area<T> calc_area(const T &t){
    typename T::type x1, x2, x3, x4, y1, y2, y3, y4;
        x1=t.a.first;
        x2=t.b.first;
        x3=t.c.first;
        x4=t.d.first;
        y1=t.a.second;
        y2=t.b.second;
        y3=t.c.second;
        y4=t.d.second;
        auto h=length(x2,y1,x2,y2);
        auto ar=((length(x1,x1,x4,y4)+length(x3,y3,x2,y2))/2)*h;
        return ar;
}
template <class T>
std::pair<T, T> calc_area(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &f){
	std::pair<T,T> v1, v2, v3;
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	Trap<T> t(v1, v2, v3);
	return calc_area(t);
}

template <class T>
Trap_center<T> calc_center(const T &t){
    typename T::type x1, x2, x3, x4, y1, y2, y3, y4;
    double xc,yc;
    x1=t.a.first;
    x2=t.b.first;
    x3=t.c.first;
    x4=t.d.first;
    y1=t.a.second;
    y2=t.b.second;
    y3=t.c.second;
    y4=t.d.second;
    xc=(x1+x2+x3+x4)/4;
    yc=(y1+y2+y3+y4)/4;
    cout << "Координаты центра трапеции: " << "(" << xc << "; " << yc << ")" << endl;
}

template <class T>
std::pair<T, T> calc_center( std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &f){
	std::pair<T,T> v1, v2, v3;
	v1 = std::get<0>(f);
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	Trap<T> t(v1, v2, v3);
	return calc_center(t);
}


template <class T>
class Romb{
    public:
    using type=T;
    using vertex=std::pair<T,T>;
    vertex a,b,c,d;
    Romb(){}
    Romb(vertex &v1, vertex &v2, vertex &v3, vertex &v4){
        a=v1;
        b=v2;
        c=v3;
        d=v4;
    }
};

template <class T>
struct is_Romb{
    static const bool value = false;
};

template <class T>
struct is_Romb<Romb<T>>{
    static const bool value = true;
};

template <class T>
using Romb_coord = typename std::enable_if<is_Romb<T>::value, void >::type;

template <class T>
using Romb_area = typename std::enable_if<is_Romb<T>::value, typename T::type >::type;

template <class T>
using Romb_center = typename std::enable_if<is_Romb<T>::value, std::pair<typename T::type, typename T::type> >::type;

template <class T>
Romb_area<T> calc_area(const T &r){
    typename T::type x1, x2, x3, x4, y1, y2, y3, y4;
        x1=r.a.first;
        x2=r.b.first;
        x3=r.c.first;
        x4=r.d.first;
        y1=r.a.second;
        y2=r.b.second;
        y3=r.c.second;
        y4=r.d.second;
    auto ar=(length(x1, y1, x3, y3)*length(x2, y2, x4, y4))/2;
    return ar;
}
template <class T>
std::pair<T, T> calc_area(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &f){
	std::pair<T,T> v1, v2, v3, v4;
	v1 = std::get<0>(f);
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	v4 = std::get<3>(f);
	Romb<T> r(v1, v2, v3, v4);
	return calc_area(r);
}

template <class T>
Romb_center<T> calc_center(const T &r){
    typename T::type x1, x2, x3, x4, xc, y1, y2, y3, y4, yc;
        x1=r.a.first;
        x2=r.b.first;
        x3=r.c.first;
        x4=r.d.first;
        y1=r.a.second;
        y2=r.b.second;
        y3=r.c.second;
        y4=r.d.second;
        xc=(x1+x2+x3+x4)/4;
        yc=(y1+y2+y3+y4)/4;
        cout << "Координаты центра ромба: " << "(" << xc << "; " << yc << ")" << endl;
}
template <class T>
std::pair<T, T> calc_center(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &f){
	std::pair<T,T> v1, v2, v3, v4;
	v1 = std::get<0>(f);
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	v4 = std::get<3>(f);
	Romb<T> r(v1, v2, v3, v4);
	return calc_center(r);
}

template <class T>
Romb_coord<T> print_coord(const T &r){
	cout << "Координаты вершин ромба: ";
    cout << "(" << r.a.first << "; " << r.a.second << ")  ";
    cout << "(" << r.b.first << "; " << r.b.second << ")  "; 
    cout << "(" << r.c.first << "; " << r.c.second << ")  "; 
    cout << "(" << r.d.first << "; " << r.d.second << ")" << endl;
}
template <class T>
std::pair<T, T> print_coord(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &f){
	std::pair<T,T> v1, v2, v3, v4;
	v1 = std::get<0>(f);
	v2 = std::get<1>(f);
	v3 = std::get<2>(f);
	v4 = std::get<3>(f);
	Romb<T> r(v1, v2, v3, v4);
	return print_coord(r);
}

template <class T>
class Pent{
    public:
    using type=T;
    using vertex=std::pair<T,T>;
    vertex cen, a, b, c, d, e;
    T r;
    Pent(){} 
    Pent(vertex &v1, T &r){
        r;
        cen=v1;
        a.first=cen.first+r*cos(0);
        b.first=cen.first+r*cos(2*pi*1/5);
        c.first=cen.first+r*cos(2*pi*2/5);
        d.first=cen.first+r*cos(2*pi*3/5);
        e.first=cen.first+r*cos(2*pi*4/5);
        a.second=cen.second+r*sin(0);
        b.second=cen.second+r*sin(2*pi*1/5);
        c.second=cen.second+r*sin(2*pi*2/5);
        d.second=cen.second+r*sin(2*pi*3/5);
        e.second=cen.second+r*sin(2*pi*4/5);
        }
};

template <class T>
struct is_Pent{
    static const bool value = false;
};

template <class T>
struct is_Pent<Pent<T>>{
    static const bool value = true;
};

template <class T>
using Pent_coord = typename std::enable_if<is_Pent<T>::value, void >::type;

template <class T>
using Pent_area = typename std::enable_if<is_Pent<T>::value, typename T::type >::type;

template <class T>
using Pent_center = typename std::enable_if<is_Pent<T>::value, std::pair<typename T::type, typename T::type> >::type;

template <class T>
Pent_area<T> calc_area(const T &p){
    typename T::type x1, x2, y1, y2;
        x1=p.a.first;
        x2=p.b.first;
        auto l=length(x1,y1,x2,y2);
        auto ar=(5/2)*l*sqrt((pow((l/(2*sin(pi/5))),2))-(pow(l,2)/4));
        return ar;
}

template <class T>
Pent_center<T> calc_center(const T &p){
    cout << "Координаты центра пятиугольника: " << "(" << p.cen.first << "; " << p.cen.second << ")" << endl;
}

template <class T>
Pent_coord<T> print_coord(const T &p){
	cout << "Координаты вершин пятиугольника: ";
    cout << "(" << p.a.first << "; " << p.a.second << ")  ";
    cout << "(" << p.b.first << "; " << p.b.second << ")  "; 
    cout << "(" << p.c.first << "; " << p.c.second << ")  "; 
    cout << "(" << p.d.first << "; " << p.d.second << ")  "; 
    cout << "(" << p.e.first << "; " << p.e.second << ")  " << endl; 
}

void Menu(){
    cout << "Введите число от 1 до 4 или 0 для действий: " << endl << 
			"1. Распечатать меню" << endl <<
			"2. Трапеция" << endl <<
			"3. Ромб" << endl <<
			"4. Пятиугольник" << endl << 
            "0. Выход из программы" << endl;
};
void Type_menu(){
    cout << "Введите число, соответствущие необходимому типу: " << endl << 
			"1. int" << endl <<
			"2. double" << endl;
};

int main(){
    cout << "Работа с геометрическими фигурами" << endl;
    int user_command=1;
    int k, j;
    using pair_int = std::pair<int, int>;
	using pair_double = std::pair<double, double>;
    std::tuple<pair_int, pair_int, pair_int> tuple_intTrap;
    std::tuple<pair_double, pair_double, pair_double> tuple_doubleTrap;
    std::tuple<pair_int, pair_int, pair_int, pair_int> tuple_intRomb;
    std::tuple<pair_double, pair_double, pair_double, pair_double> tuple_doubleRomb;
    for(;;){
    switch (user_command){
        case 1:
            Menu();
            break;
        case 2: //trap
            {Type_menu();
            cin >>k;
            switch (k){
                case 1: //int
                    {cout << "Введите координаты трёх вершин трапеции" << endl;
                    std::pair<int,int> v1, v2, v3;
                    int a, b, c, d, e, f;
                    cin >> a >> b >> c >> d >> e >> f;
                    v1.first=a;
                    v1.second=b;
                    v2.first=c;
                    v2.second=d;
                    v3.first=e;
                    v3.second=f;
                    Trap<int> t_int(v1, v2, v3);
                    print_coord(t_int);
                    cout << "Площадь трапеции: " << calc_area(t_int) << endl;
                    calc_center(t_int);
                    std::make_tuple(v1, v2, v3);}
                    break;
                case 2: //double
                    {cout << "Введите координаты трёх вершин трапеции" << endl;
                    std::pair<double,double> v1, v2, v3;
                    double a, b, c, d, e, f;
                    cin >> a >> b >> c >> d >> e >> f;
                    v1.first=a;
                    v1.second=b;
                    v2.first=c;
                    v2.second=d;
                    v3.first=e;
                    v3.second=f;
                    Trap<double> t_double(v1, v2, v3);
                    print_coord(t_double);
                    cout << "Площадь трапеции: " << calc_area(t_double) << endl;
                    calc_center(t_double);
                    std::make_tuple(v1, v2, v3);}
                    break;
                default:
                    break;}
                }
            break;
        case 3: //romb
            {Type_menu();
            cin >> k;
            switch (k){
                case 1: //int
                    {cout << "Введите координаты вершин ромба" << endl;
                    std::pair<int,int> v1, v2, v3, v4;
                    int a, b, c, d, e, f, g, h;
                    cin >> a >> b >> c >> d >> e >> f >> g >> h;
                    v1.first=a;
                    v1.second=b;
                    v2.first=c;
                    v2.second=d;
                    v3.first=e;
                    v3.second=f;
                    v4.first=g;
                    v4.second=h;
                    Romb<int> r_int(v1, v2, v3, v4);
                    print_coord(r_int);
                    cout << "Площадь ромба: " << calc_area(r_int) << endl;
                    calc_center(r_int);
                    std::make_tuple(v1, v2, v3, v4);}
                    break;
                case 2: //double
                    {cout << "Введите координаты вершин ромба" << endl;
                    std::pair<double,double> v1, v2, v3, v4;
                    double a, b, c, d, e, f, g, h;
                    cin >> a >> b >> c >> d >> e >> f >> g >> h;
                    v1.first=a;
                    v1.second=b;
                    v2.first=c;
                    v2.second=d;
                    v3.first=e;
                    v3.second=f;
                    v4.first=g;
                    v4.second=h;
                    Romb<double> r_double(v1, v2, v3, v4);
                    print_coord(r_double);
                    cout << "Площадь ромба: " << calc_area(r_double) << endl;
                    calc_center(r_double);
                    std::make_tuple(v1, v2, v3, v4);}
                    break;
                default:
                    break;}
            }
            break;
        case 4: //pent
            {Type_menu();
            cin >> k;
            switch (k){
            case 1: //int
                    {{cout << "Введите координаты центра пятиугольника и радиус описанной окружности " << endl;
                    std::pair<int,int> v1;
                    int a, b, r;
                    cin >> a >> b >> r;
                    v1.first=a;
                    v1.second=b;
                    Pent<int> p_int(v1, r);
                    print_coord(p_int);
                    cout << "Площадь пятиугольника: " << calc_area(p_int) << endl;
                    calc_center(p_int);}
                    break;
            case 2: //double
                    {cout << "Введите координаты центра пятиугольника и радиус описанной окружности " << endl;
                    std::pair<double,double> v1;
                    double a, b, r;
                    cin >> a >> b >> r;
                    v1.first=a;
                    v1.second=b;
                    Pent<double> p_double(v1, r);
                    print_coord(p_double);
                    cout << "Площадь пятиугольника: " << calc_area(p_double) << endl;
                    calc_center(p_double);}
                    break;
            default:
                break;}
                }
            break; 
        case 0:
            exit(0);
        default:
            cerr << "Нет такого пункта" << endl;
            break;
        }
        cout << endl << "Введите пункт меню: ";
        cin >> user_command;
    }
return 0;
}