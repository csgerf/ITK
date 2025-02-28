/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkMalcolmSparseLevelSetImage_h
#define itkMalcolmSparseLevelSetImage_h

#include "itkImage.h"
#include "itkLevelSetSparseImage.h"

#include "itkLabelObject.h"
#include "itkLabelMap.h"

namespace itk
{
/**
 *  \class MalcolmSparseLevelSetImage
 *  \brief Derived class for the Malcolm representation of level-set function
 *
 *  This representation is a "sparse" level-set function, where values could
 *  only be { -1, 0, +1 } and organized into 1 layer { 0 }.
 *
 *  \tparam VDimension Dimension of the input space
 *  \ingroup ITKLevelSetsv4
 */
template <unsigned int VDimension>
class ITK_TEMPLATE_EXPORT MalcolmSparseLevelSetImage : public LevelSetSparseImage<int8_t, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MalcolmSparseLevelSetImage);

  using Self = MalcolmSparseLevelSetImage;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using Superclass = LevelSetSparseImage<int8_t, VDimension>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(MalcolmSparseLevelSetImage);

  static constexpr unsigned int Dimension = VDimension;

  using typename Superclass::InputType;
  using typename Superclass::OutputType;
  using typename Superclass::OutputRealType;
  using typename Superclass::GradientType;
  using typename Superclass::HessianType;
  using typename Superclass::LevelSetDataType;

  using typename Superclass::LayerIdType;
  using typename Superclass::LabelObjectType;
  using typename Superclass::LabelObjectPointer;
  using typename Superclass::LabelObjectLengthType;
  using typename Superclass::LabelObjectLineType;

  using typename Superclass::LabelMapType;
  using typename Superclass::LabelMapPointer;
  using typename Superclass::RegionType;

  using typename Superclass::LayerType;
  using typename Superclass::LayerIterator;
  using typename Superclass::LayerConstIterator;

  using typename Superclass::LayerMapType;
  using typename Superclass::LayerMapIterator;
  using typename Superclass::LayerMapConstIterator;

  /** Returns the value of the level set function at a given location inputPixel */
  using Superclass::Evaluate;
  OutputType
  Evaluate(const InputType & inputPixel) const override;

  /** Returns the Hessian of the level set function at a given location inputPixel */
  HessianType
  EvaluateHessian(const InputType & inputPixel) const override;

  /** Returns the Laplacian of the level set function at a given location inputPixel */
  OutputRealType
  EvaluateLaplacian(const InputType & inputPixel) const override;

  /** Returns the MeanCurvature of the level set function at a given location inputPixel */
  OutputRealType
  EvaluateMeanCurvature(const InputType & inputPixel) const override;

  void
  EvaluateHessian(const InputType & inputPixel, LevelSetDataType & data) const override;
  void
  EvaluateLaplacian(const InputType & inputPixel, LevelSetDataType & data) const override;
  void
  EvaluateMeanCurvature(const InputType & inputPixel, LevelSetDataType & data) const override;

  static inline LayerIdType
  MinusOneLayer()
  {
    return -1;
  }
  static inline LayerIdType
  ZeroLayer()
  {
    return 0;
  }
  static inline LayerIdType
  PlusOneLayer()
  {
    return 1;
  }

protected:
  MalcolmSparseLevelSetImage();

  ~MalcolmSparseLevelSetImage() override = default;

  /** Initialize the sparse field layers */
  void
  InitializeLayers() override;

  void
  InitializeInternalLabelList() override;
};
} // namespace itk
#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkMalcolmSparseLevelSetImage.hxx"
#endif

#endif // itkMalcolmSparseLevelSetImage_h
