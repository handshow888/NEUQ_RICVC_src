from launch import LaunchDescription
from launch.substitutions import EnvironmentVariable
import launch.actions
from launch_ros.actions import Node


def generate_launch_description():
    use_sim_time = launch.substitutions.LaunchConfiguration('use_sim_time', default='false')
    ld = LaunchDescription()
    launch_gmapping_node = Node(
        package='slam_gmapping', 
        executable='slam_gmapping', 
        output='screen', 
        parameters=[{'use_sim_time':use_sim_time},
                    {'base_frame_': 'base_link'},  # 基座坐标系
                    {'map_frame_': 'map'},  # 地图坐标系
                    {'odom_frame_': 'odom'},  # 里程计坐标系
                    {'transform_publish_period_': 0.01},
                    {'map_update_interval_': 0.5},  # 地图更新的一个间隔，两次scanmatch的间隔，地图更新也受scanmach的影响，如果scanmatch没有成功的话，是不会更新地图的
                    {'maxRange_': 8.0},  # 激光传感器的最大测距范围
                    {'maxUrange_': 5},  # 最大有效测距范围，小于等于实际激光测距范围
                    {'sigma_': 0.05},  # 高斯模型的标准差
                    {'kernelSize_': 1},  # 卷积核大小
                    {'lstep_': 0.05},  # optimize机器人移动的初始值（距离）
                    {'astep_': 0.05},  # optimize机器人移动的初始值（角度）
                    {'iterations_': 5},  # icp的迭代次数
                    {'lsigma_': 0.075},  # 线性方向上的高斯模型标准差
                    {'ogain_': 3.0},  # 权重增益
                    {'lskip_': 0},  # 跳过的步数 为0,表示所有的激光都处理，尽可能为零，如果计算压力过大，可以改成1
                    {'srr_': 0.1},  # 预测的位移误差的方差
                    {'srt_': 0.2},  # 预测的旋转和位移之间的误差的协方差
                    {'str_': 0.1},  # 预测的旋转和位移之间的误差的协方差
                    {'stt_': 0.2},  # 预测的旋转误差的方差
                    {'linearUpdate_': 1.0},  # 线性位移的最小更新阈值
                    {'angularUpdate_': 0.5},  # 角度位移的最小更新阈值
                    {'temporalUpdate_': 1.0},  # 时间更新的阈值，-1表示禁用时间更新
                    {'resampleThreshold_': 0.5},  # 重采样阈值
                    {'particles_': 30},  # 粒子数量
                    {'xmin_': -10.0},  # 地图的最小x坐标
                    {'ymin_': -10.0},  # 地图的最小y坐标
                    {'xmax_': 10.0},  # 地图的最大x坐标
                    {'ymax_': 10.0},  # 地图的最大y坐标
                    {'delta_': 0.05},  # 地图的分辨率
                    {'occ_thresh_': 0.25},  # 标记为占据状态的阈值
                    {'llsamplerange_': 0.01},  # 线性方向上低概率采样范围
                    {'llsamplestep_': 0.01},  # 线性方向上低概率采样步长
                    {'lasamplerange_': 0.005},  # 角度方向上低概率采样范围
                    {'lasamplestep_': 0.005}  # 角度方向上低概率采样步长
                    ],
        )
    
    ld.add_action(launch_gmapping_node)
    return ld
