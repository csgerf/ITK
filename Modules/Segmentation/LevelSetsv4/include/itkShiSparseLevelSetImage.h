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

#ifndef itkShiSparseLevelSetImage_h
#define itkShiSparseLevelSetImage_h

#include "itkLevelSetSparseImage.h"

namespace itk
{
/**
 *  \class ShiSparseLevelSetImage
 *  \brief Derived class for the shi representation of level-set function
 *
 *  This representation is a "sparse" level-set function, where values could
 *  only be { -3, -1, +1, +3 } and organized into 2 layers { -1, +1 }.
 *
 *  \tparam VDimension Dimension of the input space
 *  \ingroup ITKLevelSetsv4
 */
template <unsigned int VDimension>
class ITK_TEMPLATE_EXPORT ShiSparseLevelSetImage : public LevelSetSparseImage<int8_t, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ShiSparseLevelSetImage);

  using Self = ShiSparseLevelSetImage;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using Superclass = LevelSetSparseImage<int8_t, VDimension>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ShiSparseLevelSetImage);

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

  /** Returns the value of the level set function at a given location inputIndex */
  using Superclass::Evaluate;
  OutputType
  Evaluate(const InputType & inputIndex) const override;

  /** Returns the Hessian of the level set function at a given location inputIndex */
  HessianType
  EvaluateHessian(const InputType & inputIndex) const override;

  /** Returns the Laplacian of the level set function at a given location inputIndex */
  OutputRealType
  EvaluateLaplacian(const InputType & inputIndex) const override;

  /** Returns the Laplacian of the level set function at a given location inputIndex */
  OutputRealType
  EvaluateMeanCurvature(const InputType & inputIndex) const override;

  void
  EvaluateHessian(const InputType & inputIndex, LevelSetDataType & data) const override;
  void
  EvaluateLaplacian(const InputType & inputIndex, LevelSetDataType & data) const override;
  void
  EvaluateMeanCurvature(const InputType & inputIndex, LevelSetDataType & data) const override;

  static inline LayerIdType
  MinusThreeLayer()
  {
    return -3;
  }
  static inline LayerIdType
  MinusOneLayer()
  {
    return -1;
  }
  static inline LayerIdType
  PlusOneLayer()
  {
    return 1;
  }
  static inline LayerIdType
  PlusThreeLayer()
  {
    return 3;
  }

protected:
  ShiSparseLevelSetImage();

  ~ShiSparseLevelSetImage() override = default;

  /** Initialize the sparse field layers */
  void
  InitializeLayers() override;

  void
  InitializeInternalLabelList() override;

private:
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkShiSparseLevelSetImage.hxx"
#endif

#endif // itkShiSparseLevelSetImage_h
