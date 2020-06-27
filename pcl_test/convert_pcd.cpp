#include <iostream>
#include<string.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

/*add_executable(pcd_binaryToASCII pcd_binaryToASCII.cpp)
target_link_libraries(pcd_binaryToASCII ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES}) */

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


int main(int argc, char *argv[])
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

	// 作成したPointCloudを読み込む
	// pcl::io::loadPCDFile("p_cloud_ascii.pcd", *p_cloud);
	//pcl::io::loadPCDFile("test_pcd.pcd", *p_cloud); 
	//pcl::io::loadPCDFile("bin_Laser-00147_-00849.pcd", *p_cloud);
  pcl::io::loadPCDFile(argv[1], *p_cloud);

    std::cout << "Loaded "
            << p_cloud->width * p_cloud->height
            << " data points from "<< argv[1] <<" with the following fields: "
            << std::endl;
  /*for (size_t i = 0; i < p_cloud->points.size (); ++i)
    std::cout << "    " << p_cloud->points[i].x
              << " "    << p_cloud->points[i].y
<< " " << p_cloud->points[i].z << std::endl; */

  //std::cout << argv[3] << std::endl;
    //PCLの出力
    if(strcmp(argv[3],"0") == 0){
        //pcl::PointCloud<pcl::PointXYZRGB> cloud;
      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
      u_int32_t r = 0, g = 0, b = 0;

        // Fill in the cloud data
      cloud->width    = p_cloud->width;
      cloud->height   = p_cloud->height;
      cloud->is_dense = p_cloud->is_dense;
      cloud->points.resize (p_cloud->width * p_cloud->height);

      std::cout << "p_cloud->is_dense "
            << p_cloud->is_dense
            << std::endl;

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
        /*cloud->points[i].r = r;
        cloud->points[i].g = g;
        cloud->points[i].b = b;*/
        cloud->points[i].rgb =  (r << 16) | (g << 8) |b;
/*
        std::cout << " p_cloud->points[i].r "
            << p_cloud->points[i].r
            << " \n (uint32_t)p_cloud->points[i].r "<< (uint32_t)p_cloud->points[i].r 
            <<" \n cloud->points[i].r " << cloud->points[i].r
            << std::endl;*/
      }
      //pcl::io::savePCDFileASCII ("test_ASCII_pcd.pcd", *cloud);
      pcl::io::savePCDFileASCII (argv[2], *cloud);
      //pcl::io::savePCDFileBinary (argv[2], *cloud);
      
      std::cerr << "Saved " << cloud->points.size () << " data points XYZRGB to " << argv[2] << std::endl;

    }else if(strcmp(argv[3],"1") == 0){
      //pcl::PointCloud<pcl::PointXYZRGB> cloud;
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

        // Fill in the cloud data
      cloud->width    = p_cloud->width;
      cloud->height   = p_cloud->height;
      cloud->is_dense = p_cloud->is_dense;
      cloud->points.resize (p_cloud->width * p_cloud->height);

      for (size_t i = 0; i < p_cloud->points.size (); ++i){
        cloud->points[i].x = p_cloud->points[i].x;
        cloud->points[i].y = p_cloud->points[i].y;
        cloud->points[i].z = p_cloud->points[i].z;
      }

      //pcl::io::savePCDFileASCII ("test_ASCII_pcd.pcd", *cloud);
      pcl::io::savePCDFileASCII (argv[2], *cloud);
      
      std::cerr << "Saved " << cloud->points.size () << " data points XYZ to " << argv[2] << std::endl;
    }
    
  
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