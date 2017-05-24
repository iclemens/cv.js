Haar Classifiers
----------------

This directory contains raw Haar Classifiers, e.g. those shipped with OpenCV. The XML files will be compiled into either JavaScript or shaders.

Formats
-------

JavaScript:
 * thresholds = [threshold, left_val, right_val, ..., stage threshold]
 * rects = [A, B, C, D, weight] x 3

XML (new format):
 * stages
   * stageThreshold: [stage threshold]
   * internalNodes: [node.left, node.right, node.featureIdx, threshold]
   * leafValues [left_val, right_val] 
 * features
   * rects: [A, B, C, D, weight] (repeats N times)

XML (old format):
 * stages
   * trees
     * feature
       * rects: [A, B, C, D, weight] (repeats N times)
     * threshold
     * left_val
     * right_val
   * stage_threshold
   * parent
   * next