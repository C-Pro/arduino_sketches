/*
360 degree distance memory for moving
or static distance sensor on a robot
*/

#define CENTER 90

class Scanner
{
public:
    Scanner(int step = 1);
    void    set_distance(int  direction,
                         int  distance);
    int     get_distance(int  direction);
    void    rotate(int direction);
    void    forward(int distance);
    int     get_free_way();
    int     get_start();
    int     get_end();
    int     normalize(int degree);
    int     get_median(int direction);

private:
    int scan_data[360];
    int START;
    int END;
    int STEP;
    void    init_data();
    void    calculate_boundary(int step);
};