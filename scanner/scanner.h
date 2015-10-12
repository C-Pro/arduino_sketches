/*
360 degree distance memory for moving
or static distance sensor on a robot
*/
class Scanner
{
public:
    Scanner();
    void    set_distance(int  direction,
                         int  distance);
    int     get_distance(int  direction);
    void    rotate(int direction);
    void    forward(int distance);
    int     get_free_way();
    int     normalize(int degree);
private:
    int scan_data[360];
};