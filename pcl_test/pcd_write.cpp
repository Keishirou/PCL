#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

/*add_executable(pcd_write_test pcd_write.cpp)
target_link_libraries(pcd_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
 */

int main (int argc, char** argv)
{
  //pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::PointCloud<pcl::PointXYZRGB> cloud;

  // Fill in the cloud data
  cloud.width    = 5;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    cloud.points[i].x = 1024 * 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].y = 1024 * 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].z = 1024 * 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].x *= 10.0f;
    cloud.points[i].y *= 10.0f;
    cloud.points[i].z *= 10.0f;
    cloud.points[i].r = 255;
    cloud.points[i].g = 0;
    cloud.points[i].b = 0;
  }

  pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;

  for (size_t i = 0; i < cloud.points.size (); ++i)
    std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

  return (0);
}
