#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

/*add_executable(pcd_read_test pcd_read.cpp)
target_link_libraries(pcd_read_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES}) */

using namespace std;

// ビューワー起動時の一回だけ呼ばれる
void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
	viewer.setBackgroundColor(0.2, 0.2, 0.2);
	cout << "viewerOneOff" << std::endl;
}

// ビューワー起動中の毎フレーム実行される
void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
	//cout << "viewerPsycho" << std::endl;
}


int main()
{
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr p_cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);

	// 作成したPointCloudを読み込む
	// pcl::io::loadPCDFile("p_cloud_ascii.pcd", *p_cloud);
	//pcl::io::loadPCDFile("test_pcd.pcd", *p_cloud); 
	pcl::io::loadPCDFile("bin_Laser-00147_-00849.pcd", *p_cloud);

    std::cout << "Loaded "
            << p_cloud->width * p_cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;
  for (size_t i = 0; i < p_cloud->points.size (); ++i)
    std::cout << "    " << p_cloud->points[i].x
              << " "    << p_cloud->points[i].y
<< " " << p_cloud->points[i].z << std::endl;

	// ビューワーの作成
	pcl::visualization::CloudViewer viewer("PointCloudViewer");
	viewer.showCloud(p_cloud);

	// ビューワー起動時の一回だけ呼ばれる関数をセット
	viewer.runOnVisualizationThreadOnce(viewerOneOff);

	// ビューワー起動中の毎フレーム実行される関数をセット
	viewer.runOnVisualizationThread(viewerPsycho);

	// ビューワー視聴用ループ
	while (!viewer.wasStopped())
	{

	}
	return 0;
}