from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    map_server_node = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        arguments=['/home/zllc02/navigation2_ws/map_9030.yaml']
        )

    amcl_node = Node(
        package='nav2_amcl',
        executable='amcl',
        name='amcl',
        output='screen',
        remappings=[('scan', 'scan')],
        parameters=[
            {'alpha1': 0.2},
            {'alpha2': 0.2},
            {'alpha3': 0.2},
            {'alpha4': 0.2},
            {'alpha5': 0.2},
            {'base_frame_id': 'base_footprint'},
            {'global_frame_id': 'map'},
            {'lambda_short': 0.1},
            {'laser_likelihood_max_dist': 2.0},
            {'laser_max_range': 100.0},
            {'laser_min_range': -1.0},
            {'laser_model_type': 'likelihood_field'},
            {'set_initial_pose': False},
            {'initial_pose.x': 0.0},
            {'initial_pose.y': 0.0},
            {'initial_pose.z': 0.0},
            {'initial_pose.yaw': 0.0},
            {'max_beams': 60},
            {'max_particles': 2000},
            {'min_particles': 500},
            {'odom_frame_id': 'odom'},
            {'pf_err': 0.05},
            {'pf_z': 0.99},
            {'recovery_alpha_fast': 0.0},
            {'recovery_alpha_slow': 0.0},
            {'resample_interval': 1},
            {'save_pose_rate': 0.5},
            {'sigma_hit': 0.2},
            {'tf_broadcast': True},
            {'transform_tolerance': 1.0},
            {'update_min_a': 0.2},
            {'update_min_d': 0.25},
            {'z_hit': 0.5},
            {'z_max': 0.05},
            {'z_rand': 0.5},
            {'z_short': 0.05},
            {'always_reset_initial_pose': False},
            {'scan_topic': 'scan'},
            {'map_topic': 'map'},
            {'first_map_only': False}   # Set this to true, when you want to load a new map published from the map_server

        ]
        )
    ld.add_action(map_server_node)
    ld.add_action(amcl_node)
    return ld
