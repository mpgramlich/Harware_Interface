#ifndef RADIO_NAV_HPP__
#define RADIO_NAV_HPP__

#include <math.h>

#define PI 3.14159265

class radio_nav
{
  class radio
  {
  public:

    double distl, distr;
    double x, y;
    double angle;
    bool isTriangle;
    radio(){
    };


  };

  double base_station;
  radio rad0;
  radio rad1;
  double bearing;
  double heading;

public:

  radio_nav();
  void set_base_station_distance(double& base_station_distance);
  void set_rad0_distl(double& distance_to_left_rad);
  void set_rad0_distr(double& distance_to_right_rad);
  void set_rad1_distl(double& distance_to_left_rad);
  void set_rad1_distr(double& distance_to_right_rad);
  void set_all(double& dist_base_station, double& dist0_l, double& dist0_r, double& dist1_l, double& dist1_r);
  void triangulate();
  double get_rad0_x();
  double get_rad0_y();
  double get_rad0_angle();
  double get_rad1_x();
  double get_rad1_y();
  double get_rad1_angle();
  double get_heading();
  double get_bearing();
  bool success();

};

radio_nav::radio_nav(){
  rad0.isTriangle = false;
  rad1.isTriangle = false;
};

void radio_nav::set_base_station_distance(double& base_station_distance){
  base_station = base_station_distance;
}

void radio_nav::set_rad0_distl(double& distance_to_left_rad){
  rad0.distl = distance_to_left_rad;
}

void radio_nav::set_rad0_distr(double& distance_to_right_rad){
  rad0.distr = distance_to_right_rad;
}

void radio_nav::set_rad1_distl(double& distance_to_left_rad){
  rad1.distl = distance_to_left_rad;
}

void radio_nav::set_rad1_distr(double& distance_to_right_rad){
  rad1.distr = distance_to_right_rad;
}

void radio_nav::set_all(double& dist_base_station, double& dist0_l, double& dist0_r, double& dist1_l, double& dist1_r){
  base_station = dist_base_station;
  rad0.distl = dist0_l;
  rad0.distr = dist0_r;
  rad1.distl = dist1_l;
  rad1.distr = dist1_r;
}

void radio_nav::triangulate(){

  double temp;

  //triangulation of rad 0
  temp = pow(rad0.distr,2.0) + pow(base_station,2.0) - pow(rad0.distl,2.0);
  if (temp/(2.0 * base_station * rad0.distr) >= -1 && temp/(2.0 * base_station * rad0.distr) <= 1){
    rad0.angle = acos(temp/(2.0 * base_station * rad0.distr));
    rad0.x = (rad0.distr * cos(rad0.angle)) - (base_station/(2.0));
    rad0.y = rad0.distr * sin(rad0.angle);

    if (rad0.x == 0 && rad0.y >= 0){
      rad0.angle = PI / 2.0;
    }else if (rad0.x == 0 && rad0.y < 0){
      rad0.angle = -1 * PI / 2.0;
    }else if (rad0.x < 0){
      rad0.angle = atan(rad0.y/rad0.x) + PI;
    }else {
      rad0.angle = atan(rad0.y/rad0.x);
    }

    rad0.isTriangle = true;
  }

  //triangulation of rad_1
  temp = (pow(rad1.distr,2.0) + pow(base_station,2.0) - pow(rad1.distl,2.0));
  if (temp/(2.0 * base_station * rad1.distr) >= -1 && temp/(2.0 * base_station * rad1.distr) <= 1){
    rad1.angle = acos(temp/(2.0 * base_station * rad1.distr));
    rad1.x = (rad1.distr * cos(rad1.angle)) - (base_station/(2.0));
    rad1.y = rad1.distr * sin(rad1.angle);

    if (rad1.x == 0 && rad1.y >= 0){
      rad1.angle = PI / 2.0;
    }else if (rad1.x == 0 && rad1.y < 0){
      rad1.angle = -1 * PI / 2.0;
    }else if (rad1.x < 0){
      rad1.angle = atan(rad1.y/rad1.x) + PI;
    }else {
      rad1.angle = atan(rad1.y/rad1.x);
    }
    
    rad1.isTriangle = true;
  }

  if (rad0.isTriangle && rad1.isTriangle){
    //calculate bearing
    if ((rad1.x + rad0.x) == 0 && (rad1.y + rad0.y) >= 0){
      bearing = PI / 2.0;
    } else if ((rad1.x + rad0.x) == 0 && (rad1.y + rad0.y) < 0){
      bearing = -1 * PI / 2.0;
    }else if ((rad1.x + rad0.x) < 0){
      bearing = atan(((rad1.y + rad0.y)/2.0) / ((rad1.x + rad0.x)/2.0)) + PI;
    } else {
      bearing = atan(((rad1.y + rad0.y)/2.0) / ((rad1.x + rad0.x)/2.0));
    }

    //calculate heading
    if ((rad1.x - rad0.x) == 0 && (rad1.y - rad0.y) >= 0){
      heading = PI / 2.0;
    }else if ((rad1.x - rad0.x) == 0 && (rad1.y - rad0.y) < 0){
      heading = -1 * PI / 2.0;
    }else if ((rad1.x - rad0.x) < 0){
      heading = atan((rad1.y - rad0.y) / (rad1.x - rad0.x)) + PI;
    }else {
      heading = atan((rad1.y - rad0.y) / (rad1.x - rad0.x));
    }
  }

}



double radio_nav::get_rad0_x(){
  return rad0.x;
}

double radio_nav::get_rad0_y(){
  return rad0.y;
}

double radio_nav::get_rad0_angle(){
  return rad0.angle;
}

double radio_nav::get_rad1_x(){
  return rad1.x;
}

double radio_nav::get_rad1_y(){
  return rad1.y;
}

double radio_nav::get_rad1_angle(){
  return rad1.angle;
}

double radio_nav::get_heading(){
  return heading;
}

double radio_nav::get_bearing(){
  return bearing;
}

bool radio_nav::success(){
  return (rad0.isTriangle && rad1.isTriangle);
}

#endif // RADIO_NAV_HPP__
