/*
 Copyright (C) 2010  ARToolkitPlus Authors

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Authors:
 Daniel Wagner
 Pavel Rojtberg
 */

#ifndef __ARTOOLKITPLUS_TRACKERSINGLEMARKERIMPL_HEADERFILE__
#define __ARTOOLKITPLUS_TRACKERSINGLEMARKERIMPL_HEADERFILE__

#include <ARToolKitPlus/TrackerSingleMarker.h>
#include <ARToolKitPlus/TrackerImpl.h>

#define TrackerSingleMarkerImpl TrackerSingleMarkerImpl

namespace ARToolKitPlus {

/// TrackerSingleMarkerImpl implements the TrackerSingleMarker interface
/**
 *  __PATTERN_SIZE_X describes the pattern image width (16 by default).
 *  __PATTERN_SIZE_Y describes the pattern image height (16 by default).
 *  __PATTERN_SAMPLE_NUM describes the maximum resolution at which a pattern is sampled from the camera image
 *  (64 by default, must a a multiple of __PATTERN_SIZE_X and __PATTERN_SIZE_Y).
 *  maxLoadPatterns describes the maximum number of pattern files that can be loaded.
 *  __MAX_IMAGE_PATTERNS describes the maximum number of patterns that can be analyzed in a camera image.
 *  Reduce maxLoadPatterns and __MAX_IMAGE_PATTERNS to reduce memory footprint.
 */
class TrackerSingleMarkerImpl: public TrackerSingleMarker, protected TrackerImpl {
public:
	TrackerSingleMarkerImpl(int nWidth, int nHeight, int maxLoadPatterns = 0);
	~TrackerSingleMarkerImpl();

	/// initializes TrackerSingleMarker
	/**
	 *  nCamParamFile is the name of the camera parameter file
	 *  nLogger is an instance which implements the ARToolKit::Logger interface
	 */
	virtual bool init(const char* nCamParamFile, ARFloat nNearClip, ARFloat nFarClip);

	/// adds a pattern to ARToolKit
	/**
	 *  pass the patterns filename
	 */
	virtual int addPattern(const char* nFileName);

	/// calculates the transformation matrix
	/**
	 *	pass the image as RGBX (32-bits)
	 */
	virtual vector<int> calc(const uint8_t* nImage, ARMarkerInfo** nMarker_info = NULL, int* nNumMarkers = NULL);

	/// Sets the width and height of the patterns.
	virtual void setPatternWidth(ARFloat nWidth) {
		patt_width = nWidth;
	}

	/// Provides access to ARToolKit' patt_trans matrix
	/**
	 *  This method is primarily for compatibility issues with code previously using
	 *  ARToolKit rather than ARToolKitPlus. patt_trans is the original transformation
	 *  matrix ARToolKit calculates rather than the OpenGL style version of this matrix
	 *  that can be retrieved via getModelViewMatrix().
	 */
	virtual void getARMatrix(ARFloat nMatrix[3][4]) const;

	/// Returns the confidence value of the currently best detected marker.
	virtual ARFloat getConfidence() const {
		return confidence;
	}

	virtual void selectDetectedMarker(const int id);

	virtual int selectBestMarkerByCf();

	//
	// reimplement TrackerImpl into TrackerSingleMarker interface
	//
	// TODO: something like 'using cleanup;' would be nicer but does seem to work...
	//
	void cleanup() {
		TrackerImpl::cleanup();
	}
	bool setPixelFormat(PIXEL_FORMAT nFormat) {
		return TrackerImpl::setPixelFormat(nFormat);
	}
	bool loadCameraFile(const char* nCamParamFile, ARFloat nNearClip, ARFloat nFarClip) {
		return TrackerImpl::loadCameraFile(nCamParamFile, nNearClip, nFarClip);
	}
	void setLoadUndistLUT(bool nSet) {
		TrackerImpl::setLoadUndistLUT(nSet);
	}
	int arDetectMarker(uint8_t *dataPtr, int thresh, ARMarkerInfo **marker_info, int *marker_num) {
		return TrackerImpl::arDetectMarker(dataPtr, thresh, marker_info, marker_num);
	}
	int arDetectMarkerLite(uint8_t *dataPtr, int thresh, ARMarkerInfo **marker_info, int *marker_num) {
		return TrackerImpl::arDetectMarkerLite(dataPtr, thresh, marker_info, marker_num);
	}
	ARFloat arMultiGetTransMat(ARMarkerInfo *marker_info, int marker_num, ARMultiMarkerInfoT *config) {
		return TrackerImpl::arMultiGetTransMat(marker_info, marker_num, config);
	}
	ARFloat arGetTransMat(ARMarkerInfo *marker_info, ARFloat center[2], ARFloat width, ARFloat conv[3][4]) {
		return TrackerImpl::arGetTransMat(marker_info, center, width, conv);
	}
	ARFloat arGetTransMatCont(ARMarkerInfo *marker_info, ARFloat prev_conv[3][4], ARFloat center[2], ARFloat width,
			ARFloat conv[3][4]) {
		return TrackerImpl::arGetTransMatCont(marker_info, prev_conv, center, width, conv);
	}
	ARFloat rppMultiGetTransMat(ARMarkerInfo *marker_info, int marker_num, ARMultiMarkerInfoT *config) {
		return TrackerImpl::rppMultiGetTransMat(marker_info, marker_num, config);
	}
	ARFloat rppGetTransMat(ARMarkerInfo *marker_info, ARFloat center[2], ARFloat width, ARFloat conv[3][4]) {
		return TrackerImpl::rppGetTransMat(marker_info, center, width, conv);
	}
	int arLoadPatt(char *filename) {
		return TrackerImpl::arLoadPatt(filename);
	}
	int arFreePatt(int patno) {
		return TrackerImpl::arFreePatt(patno);
	}
	int arMultiFreeConfig(ARMultiMarkerInfoT *config) {
		return TrackerImpl::arMultiFreeConfig(config);
	}
	ARMultiMarkerInfoT *arMultiReadConfigFile(const char *filename) {
		return TrackerImpl::arMultiReadConfigFile(filename);
	}
	void activateBinaryMarker(int nThreshold) {
		TrackerImpl::activateBinaryMarker(nThreshold);
	}
	void setMarkerMode(MARKER_MODE nMarkerMode) {
		TrackerImpl::setMarkerMode(nMarkerMode);
	}
	void activateVignettingCompensation(bool nEnable, int nCorners = 0, int nLeftRight = 0, int nTopBottom = 0) {
		TrackerImpl::activateVignettingCompensation(nEnable, nCorners, nLeftRight, nTopBottom);
	}
	void changeCameraSize(int nWidth, int nHeight) {
		TrackerImpl::changeCameraSize(nWidth, nHeight);
	}
	void setUndistortionMode(UNDIST_MODE nMode) {
		TrackerImpl::setUndistortionMode(nMode);
	}
	bool setPoseEstimator(POSE_ESTIMATOR nMethod) {
		return TrackerImpl::setPoseEstimator(nMethod);
	}
	void setHullMode(HULL_TRACKING_MODE nMode) {
		TrackerImpl::setHullMode(nMode);
	}
	void setBorderWidth(ARFloat nFraction) {
		TrackerImpl::setBorderWidth(nFraction);
	}
	void setThreshold(int nValue) {
		TrackerImpl::setThreshold(nValue);
	}
	int getThreshold() const {
		return TrackerImpl::getThreshold();
	}
	void activateAutoThreshold(bool nEnable) {
		TrackerImpl::activateAutoThreshold(nEnable);
	}
	bool isAutoThresholdActivated() const {
		return TrackerImpl::isAutoThresholdActivated();
	}
	void setNumAutoThresholdRetries(int nNumRetries) {
		TrackerImpl::setNumAutoThresholdRetries(nNumRetries);
	}
	const ARFloat* getModelViewMatrix() const {
		return TrackerImpl::getModelViewMatrix();
	}
	const ARFloat* getProjectionMatrix() const {
		return TrackerImpl::getProjectionMatrix();
	}
	const char* getDescription() {
		return TrackerImpl::getDescription();
	}
	PIXEL_FORMAT getPixelFormat() const {
		return static_cast<PIXEL_FORMAT> (TrackerImpl::getPixelFormat());
	}
	int getBitsPerPixel() const {
		return static_cast<PIXEL_FORMAT> (TrackerImpl::getBitsPerPixel());
	}
	int getNumLoadablePatterns() const {
		return TrackerImpl::getNumLoadablePatterns();
	}
	void setImageProcessingMode(IMAGE_PROC_MODE nMode) {
		TrackerImpl::setImageProcessingMode(nMode);
	}
	Camera* getCamera() {
		return TrackerImpl::getCamera();
	}
	void setCamera(Camera* nCamera) {
		TrackerImpl::setCamera(nCamera);
	}
	void setCamera(Camera* nCamera, ARFloat nNearClip, ARFloat nFarClip) {
		TrackerImpl::setCamera(nCamera, nNearClip, nFarClip);
	}
	ARFloat calcOpenGLMatrixFromMarker(ARMarkerInfo* nMarkerInfo, ARFloat nPatternCenter[2], ARFloat nPatternSize,
			ARFloat *nOpenGLMatrix) {
		return TrackerImpl::calcOpenGLMatrixFromMarker(nMarkerInfo, nPatternCenter, nPatternSize, nOpenGLMatrix);
	}
	ARFloat executeSingleMarkerPoseEstimator(ARMarkerInfo *marker_info, ARFloat center[2], ARFloat width,
			ARFloat conv[3][4]) {
		return TrackerImpl::executeSingleMarkerPoseEstimator(marker_info, center, width, conv);
	}
	ARFloat executeMultiMarkerPoseEstimator(ARMarkerInfo *marker_info, int marker_num, ARMultiMarkerInfoT *config) {
		return TrackerImpl::executeMultiMarkerPoseEstimator(marker_info, marker_num, config);
	}
	const CornerPoints& getTrackedCorners() const {
		return TrackerImpl::getTrackedCorners();
	}

	size_t getMemoryRequirements();

protected:
	ARFloat confidence;
	ARFloat patt_width;
	ARFloat patt_center[2];
	ARFloat patt_trans[3][4];
	// save the results of last calc call
	ARMarkerInfo *marker_info;
	int marker_num;
};

} // namespace ARToolKitPlus

#endif //__ARTOOLKITPLUS_TRACKERSINGLEMARKERIMPL_HEADERFILE__
