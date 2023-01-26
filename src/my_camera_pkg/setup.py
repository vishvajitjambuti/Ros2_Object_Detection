from setuptools import setup

package_name = 'my_camera_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='vishvajit',
    maintainer_email='vishvajitjambuti003@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'camera_pub = my_camera_pkg.camera_pub:main',
            'camera_sub = my_camera_pkg.camera_sub:main',
            '2camera_pub = my_camera_pkg.2camera_pub:main',
            '2camera_sub = my_camera_pkg.2camera_sub:main',
            'camera_stride_pub = my_camera_pkg.camera_stride_pub:main',
        ],
    },
)
