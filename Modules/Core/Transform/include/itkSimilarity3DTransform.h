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
#ifndef itkSimilarity3DTransform_h
#define itkSimilarity3DTransform_h

#include <iostream>
#include "itkVersorRigid3DTransform.h"

namespace itk
{
/** \class Similarity3DTransform
 * \brief Similarity3DTransform of a vector space (e.g. space coordinates)
 *
 * This transform applies a rotation, translation and isotropic scaling to the space.
 *
 * The parameters for this transform can be set either using individual Set
 * methods or in serialized form using SetParameters() and SetFixedParameters().
 *
 * The serialization of the optimizable parameters is an array of 7 elements.
 * The first 3 elements are the components of the versor representation
 * of 3D rotation. The next 3 parameters defines the translation in each
 * dimension. The last parameter defines the isotropic scaling.
 *
 * The serialization of the fixed parameters is an array of 3 elements defining
 * the center of rotation.
 *
 *
 * \sa VersorRigid3DTransform
 * \ingroup ITKTransform
 */
template <typename TParametersValueType = double>
class ITK_TEMPLATE_EXPORT Similarity3DTransform : public VersorRigid3DTransform<TParametersValueType>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(Similarity3DTransform);

  /** Standard class type aliases. */
  using Self = Similarity3DTransform;
  using Superclass = VersorRigid3DTransform<TParametersValueType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** New macro for creation of through a Smart Pointer. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(Similarity3DTransform);

  /** Dimension of parameters. */
  static constexpr unsigned int SpaceDimension = 3;
  static constexpr unsigned int InputSpaceDimension = 3;
  static constexpr unsigned int OutputSpaceDimension = 3;
  static constexpr unsigned int ParametersDimension = 7;

  /** Parameters Type   */
  using typename Superclass::ParametersType;
  using typename Superclass::FixedParametersType;
  using typename Superclass::JacobianType;
  using typename Superclass::JacobianPositionType;
  using typename Superclass::InverseJacobianPositionType;
  using typename Superclass::ScalarType;
  using typename Superclass::InputPointType;
  using typename Superclass::OutputPointType;
  using typename Superclass::InputVectorType;
  using typename Superclass::OutputVectorType;
  using typename Superclass::InputVnlVectorType;
  using typename Superclass::OutputVnlVectorType;
  using typename Superclass::InputCovariantVectorType;
  using typename Superclass::OutputCovariantVectorType;
  using typename Superclass::MatrixType;
  using typename Superclass::InverseMatrixType;
  using typename Superclass::CenterType;
  using typename Superclass::OffsetType;
  using typename Superclass::TranslationType;

  /** Versor type. */
  using typename Superclass::VersorType;
  using typename Superclass::AxisType;
  using typename Superclass::AngleType;
  using ScaleType = TParametersValueType;

  /** Set the parameters to the IdentityTransform */
  void
  SetIdentity() override;

  /** Directly set the rotation matrix of the transform.
   *
   * \warning The input matrix must be orthogonal with isotropic scaling
   * to within a specified tolerance, else an exception is thrown.
   *
   * \sa MatrixOffsetTransformBase::SetMatrix() */
  void
  SetMatrix(const MatrixType & matrix) override;

  /** Directly set the rotation matrix of the transform.
   *
   * \warning The input matrix must be orthogonal with isotropic scaling
   * to within the specified tolerance, else an exception is thrown.
   *
   * \sa MatrixOffsetTransformBase::SetMatrix() */
  void
  SetMatrix(const MatrixType & matrix, const TParametersValueType tolerance) override;

  /** Set the transformation from a container of parameters This is typically
   * used by optimizers.  There are 7 parameters. The first three represent the
   * versor, the next three represent the translation and the last one
   * represents the scaling factor. */
  void
  SetParameters(const ParametersType & parameters) override;

  const ParametersType &
  GetParameters() const override;

  /** Set/Get the value of the isotropic scaling factor */
  void
  SetScale(ScaleType scale);

  itkGetConstReferenceMacro(Scale, ScaleType);

  /** This method computes the Jacobian matrix of the transformation.
   * given point or vector, returning the transformed point or
   * vector. The rank of the Jacobian will also indicate if the
   * transform is invertible at this point. */
  void
  ComputeJacobianWithRespectToParameters(const InputPointType & p, JacobianType & jacobian) const override;

protected:
  Similarity3DTransform(const MatrixType & matrix, const OutputVectorType & offset);
  Similarity3DTransform(unsigned int paramDim);
  Similarity3DTransform();
  ~Similarity3DTransform() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** Recomputes the matrix by calling the Superclass::ComputeMatrix() and then
   * applying the scale factor. */
  void
  ComputeMatrix() override;

  /** Computes the parameters from an input matrix. */
  void
  ComputeMatrixParameters() override;

private:
  ScaleType m_Scale{};
}; // class Similarity3DTransform
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkSimilarity3DTransform.hxx"
#endif

#endif /* itkSimilarity3DTransform_h */
