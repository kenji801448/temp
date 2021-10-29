pid_pid = PIDCtrl()
pid_cpst = PIDCtrl()
pid_speed = PIDCtrl()
pid_pitch = PIDCtrl()
pid_Follow_Line = PIDCtrl()
list_Line = RmList()
variable_Agv = 0
variable_x = 0
variable_K = 0
variable_v = 0
variable_P = 0
def start():
    global variable_Agv
    global variable_x
    global variable_K
    global variable_v
    global variable_P
    global list_Line
    global pid_pid
    global pid_cpst
    global pid_speed
    global pid_pitch
    global pid_Follow_Line
    robot_ctrl.set_mode(rm_define.robot_mode_chassis_follow)
    gimbal_ctrl.rotate_with_degree(rm_define.gimbal_down,20)
    vision_ctrl.enable_detection(rm_define.vision_detection_line)
    vision_ctrl.line_follow_color_set(rm_define.line_follow_color_blue)
    chassis_ctrl.set_trans_speed(0.5)
    pid_Follow_Line.set_ctrl_params(200,0,20)
    while True:
        list_Line=RmList(vision_ctrl.get_line_detection_info())
        if list_Line[2] >= 1:
            variable_x = list_Line[15]
            pid_Follow_Line.set_error(variable_x - 0.5)
            variable_P = pid_Follow_Line.get_output()
            gimbal_ctrl.rotate_with_speed(variable_P,0)
            chassis_ctrl.move(0)
        else:
            gimbal_ctrl.rotate_with_speed(0,0)
            chassis_ctrl.stop()
