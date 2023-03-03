#include <iostream>
#include <vector>
using namespace std;

class ControlPoint{
    private:
        int x, y;
    public:
        ControlPoint() : x(0), y(0) {}
        ControlPoint(int x, int y) : x(x), y(y) {}
        int getx() {return x;}
        int gety() {return y;} 
};
/*1. zadatak*/
class BezierSpline{
    private:
        ControlPoint P1;
        ControlPoint P2;
        ControlPoint P3;
        ControlPoint P4;
        float t;
    public:
        BezierSpline() : P1(0,0), P2(0,0), P3(0,0), P4(0,0), t(0) {}
        BezierSpline(ControlPoint p1, ControlPoint p2, ControlPoint p3, ControlPoint p4, float t) : P1(p1), P2(p2), P3(p3), P4(p4), t(t) {} 
        vector<float> GetPoint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float t){
            vector<float> arr_x;
            vector<float> arr_y;
            arr_x.push_back(x1);
            arr_x.push_back(x2);
            arr_x.push_back(x3);
            arr_x.push_back(x4);
            arr_y.push_back(y1);
            arr_y.push_back(y2);
            arr_y.push_back(y3);
            arr_y.push_back(y4);

            int n = 4;
            for (int k = 1; k < n; k++){
                for (int i = 0; i < n-k; i++){
                    /*cout << arr_x[i+1] << " ";*/
                    arr_x[i] = (1-t)*arr_x[i] + t*arr_x[i+1];
                    arr_y[i] = (1-t)*arr_y[i] + t*arr_y[i+1];
                }
            }
            vector<float> result;
            result.push_back(arr_x[0]);
            result.push_back(arr_x[1]);
            result.push_back(arr_x[2]);
            result.push_back(arr_x[3]);
            result.push_back(arr_y[0]);
            result.push_back(arr_y[1]);
            result.push_back(arr_y[2]);
            result.push_back(arr_y[3]);
            return result;
        }
        /*3.zadatak*/
        ControlPoint getP12(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.P1.getx()+t*spline.P2.getx(), (1-t)*spline.P1.gety()+t*spline.P2.gety());
            return new_point;
        }

        ControlPoint getP23(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.P2.getx()+t*spline.P3.getx(), (1-t)*spline.P2.gety()+t*spline.P3.gety());
            return new_point;
        }

        ControlPoint getP34(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.P3.getx()+t*spline.P4.getx(), (1-t)*spline.P3.gety()+t*spline.P4.gety());
            return new_point;
        }

        ControlPoint getP123(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.getP12(spline, t).getx()+t*spline.getP23(spline,t).getx(), (1-t)*spline.getP12(spline, t).gety()+t*spline.getP23(spline,t).gety());
            return new_point;
        }

        ControlPoint getP234(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.getP23(spline, t).getx()+t*spline.getP34(spline,t).getx(), (1-t)*spline.getP23(spline, t).gety()+t*spline.getP34(spline,t).gety());
            return new_point;
        }

        ControlPoint getP1234(BezierSpline spline, float t){
            ControlPoint new_point((1-t)*spline.getP123(spline, t).getx()+t*spline.getP234(spline,t).getx(), (1-t)*spline.getP123(spline, t).gety()+t*spline.getP234(spline,t).gety());
            return new_point;
        }

        pair<BezierSpline, BezierSpline> SubdivideBezier(BezierSpline spline, float t){
            BezierSpline first_half(spline.P1, spline.getP12(spline, t), spline.getP123(spline, t), spline.getP1234(spline, t), t);
            BezierSpline second_half(spline.getP1234(spline, t), spline.getP234(spline, t), spline.getP34(spline, t), spline.P4, t);

            return make_pair(first_half, second_half);
        }

};

/*2. zadatak*/
class HermiteSpline{
    private:
        ControlPoint P1;
        ControlPoint P2;
        ControlPoint P3;
        ControlPoint P4;
        float t;
    public:
        HermiteSpline() : P1(0,0), P2(0,0), P3(0,0), P4(0,0), t(0) {}
        HermiteSpline(ControlPoint p1, ControlPoint p2, ControlPoint p3, ControlPoint p4, float t) : P1(p1), P2(p2), P3(p3), P4(p4), t(t) {}
        vector<float> BezierToHermite(BezierSpline b){
            vector<float> bezierSpline = b.GetPoint(P1.getx(), P1.gety(), P2.getx(), P2.gety(), P3.getx(), P3.gety(), P4.getx(), P4.gety(), 0.5);
            vector<float> result;

            result.push_back(bezierSpline[0]);
            result.push_back(3*(bezierSpline[1] - bezierSpline[0]));
            result.push_back(bezierSpline[2]);
            result.push_back(3*(bezierSpline[3] - bezierSpline[2]));
            result.push_back(bezierSpline[4]);
            result.push_back(3*(bezierSpline[5] - bezierSpline[4]));
            result.push_back(bezierSpline[6]);
            result.push_back(3*(bezierSpline[7] - bezierSpline[6]));

            return result;
        }
};



int main(){
    ControlPoint P1(0,0);
    ControlPoint P2(2,4);
    ControlPoint P3(6,4);
    ControlPoint P4(8,0);
    BezierSpline spline(P1, P2, P3, P4, 0.5);
    cout << "Vrijednost Bezierovog splinea za t = 0.5: " << "(" << spline.GetPoint(P1.getx(), P1.gety(), P2.getx(), P2.gety(), P3.getx(), P3.gety(), P4.getx(), P4.gety(), 0.5)[0] << ", " << spline.GetPoint(P1.getx(), P1.gety(), P2.getx(), P2.gety(), P3.getx(), P3.gety(), P4.getx(), P4.gety(), 0.5)[4] << ")" << endl;
    HermiteSpline hspline(P1, P2, P3, P4, 0.5);
    vector<float> bezier_to_hermite = hspline.BezierToHermite(spline);
    cout << "Hermite ekvivalentan Bezierovom spline-u je: " << endl;
    cout << "P0 = (" << bezier_to_hermite[0] << ", " << bezier_to_hermite[4] << ")" << endl;
    cout << "P1 = (" << bezier_to_hermite[1] << ", " << bezier_to_hermite[5] << ")" << endl;
    cout << "P2 = (" << bezier_to_hermite[2] << ", " << bezier_to_hermite[6] << ")" << endl;
    cout << "P3 = (" << bezier_to_hermite[3] << ", " << bezier_to_hermite[7] << ")" << endl;

    pair<BezierSpline,BezierSpline> segmented = spline.SubdivideBezier(spline, 0.5);

    /*cout << segmented.first.P1 << ", " << segmented.first.P2 << ", " << segmented.first.P3 << ", " << segmented.first.P4 << endl;*/
    /*cout << segmented.second.P1 << ", " << segmented.second.P2 << ", " << segmented.second.P3 << ", " << segmented.second.P4 << endl;*/

    return 0;
}