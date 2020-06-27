#include <iostream>
#include<string.h>
#include <pcl/io/pcd_io.h>

using namespace std;

int main(int argc, char *argv[])
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

	// 作成したPointCloudを読み込む
  pcl::io::loadPCDFile(argv[1], *p_cloud);

  std::cout << "Loaded "
          << p_cloud->width * p_cloud->height
          << " data points from "<< argv[1] 
          << std::endl;

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  u_int32_t r = 0, g = 0, b = 0;

    // Fill in the cloud data
  cloud->width    = p_cloud->width;
  cloud->height   = p_cloud->height;
  cloud->is_dense = p_cloud->is_dense;
  cloud->points.resize (p_cloud->width * p_cloud->height);

  for (size_t i = 0; i < p_cloud->points.size (); ++i){
    cloud->points[i].x = p_cloud->points[i].x;
    cloud->points[i].y = p_cloud->points[i].y;
    cloud->points[i].z = p_cloud->points[i].z;
    cloud->points[i].r = (uint32_t)p_cloud->points[i].r;
    cloud->points[i].g = (uint32_t)p_cloud->points[i].g;
    cloud->points[i].b = (uint32_t)p_cloud->points[i].b;
    r = p_cloud->points[i].r;
    g = p_cloud->points[i].g;
    b = p_cloud->points[i].b;
    cloud->points[i].rgb =  (r << 16) | (g << 8) |b;
  }
  pcl::io::savePCDFileASCII (argv[2], *cloud);
  
  std::cerr << "Saved " << cloud->points.size () << " data points XYZRGB to " << argv[2] << std::endl;

	return 0;
}