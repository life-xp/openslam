#ifndef OPENSLAM_SLAM_MAP_POINT_H_
#define OPENSLAM_SLAM_MAP_POINT_H_

#include <openslam/slam/link_pragmas.h>
#include <list>
#include <memory>
#include <mutex>
#include <opencv2/core/core.hpp>

namespace openslam
{
	namespace slam
	{
		class Feature;

		class SLAM_IMPEXP MapPoint
		{
		public:
			MapPoint(const cv::Mat &pos, Feature * cur_obs);
			~MapPoint();
			/** \brief map point 在世界坐标系中的位置
			*/
			cv::Mat getWorldPosition();

			/**添加观测到的对应特征*/
			void addFeatureRef(Feature* ftr);

			/** \brief 计算对同一个mappoint所有对应的所有特征的描述子进行处理，寻找最好描述子
			*/
			void computeDistinctiveDescriptors();

			/** \brief 更新map point的法向量及对应可能的最大最小深度
			*/
			void updateNormalAndDepth();

		public:
			long unsigned int id_;                                   //!< 点唯一的id
			static long unsigned int map_point_counter_;             //!< 创建点的计数，用于设置唯一的id
			cv::Mat world_position_;                                 //!<在世界坐标系中的位置
			cv::Mat normal_vector_;                                  //!<平均观测方向
			std::list<Feature*>   obs_;                              //!< 对应这个点的所有特征
			Feature * cur_obs_;//!<对应这个map point 的当前特征
			int obs_num_;                                            //!< 观察到该map point的关键帧的个数
			std::mutex mutex_features_;//!< 对点对应的特征读写进行控制
			std::mutex mutex_position_;//!< 对点对应的位置进行读写控制
			cv::Mat descriptor_;//!<得到该map point 对应的最好描述子（与其他关键帧对该点的描述距离较小）
			float min_distance_;//!<尺度不变，有效观察距离最小值
			float max_distance_;//!<尺度不变，有效观察距离最大值
		};

	}
}

#endif // OPENSLAM_SLAM_MAP_POINT_H_
