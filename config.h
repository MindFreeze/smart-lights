HC_SR04 hc_sr04[] = {
    HC_SR04(Point(0, 0), Point(1, 0), 13, 11),
};
// Point strip1Points[] = {Point(100, 0), Point(100, 400)};
WS2811strip ws2811[] = {
    WS2811strip(Point(0, 0), TURN_POINTS(Point(100, 0), Point(100, 400)), 50, 7, NEO_GRB + NEO_KHZ400),
};
