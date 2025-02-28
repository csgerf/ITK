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
#ifndef itkVnlFFTImageFilterInitFactory_h
#define itkVnlFFTImageFilterInitFactory_h
#include "ITKFFTExport.h"

#include "itkLightObject.h"

namespace itk
{
/**
 * \class VnlFFTImageFilterInitFactory
 * \brief Initialize Vnl FFT image filter factory backends.
 *
 * The purpose of VnlFFTImageFilterInitFactory is to perform
 * one-time registration of factory objects that handle
 * creation of Vnl-backend FFT image filter classes
 * through the ITK object factory singleton mechanism.
 *
 * \ingroup ITKFFT
 */
class ITKFFT_EXPORT VnlFFTImageFilterInitFactory : public LightObject
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(VnlFFTImageFilterInitFactory);

  /** Standard class type aliases. */
  using Self = VnlFFTImageFilterInitFactory;
  using Superclass = LightObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(VnlFFTImageFilterInitFactory);

  /** Mimic factory interface for Python initialization  */
  static void
  RegisterOneFactory()
  {
    RegisterFactories();
  }

  /** Register all Vnl FFT factories */
  static void
  RegisterFactories();

protected:
  VnlFFTImageFilterInitFactory();
  ~VnlFFTImageFilterInitFactory() override;
};
} // end namespace itk

#endif
