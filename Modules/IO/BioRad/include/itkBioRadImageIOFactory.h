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
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef itkBioRadImageIOFactory_h
#define itkBioRadImageIOFactory_h
#include "ITKIOBioRadExport.h"

#include "itkObjectFactoryBase.h"
#include "itkImageIOBase.h"

namespace itk
{
/**
 * \class BioRadImageIOFactory
 * \brief Create instances of BioRadImageIO objects using an object factory.
 * \ingroup ITKIOBioRad
 */
class ITKIOBioRad_EXPORT BioRadImageIOFactory : public ObjectFactoryBase
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(BioRadImageIOFactory);

  /** Standard class type aliases. */
  using Self = BioRadImageIOFactory;
  using Superclass = ObjectFactoryBase;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Class Methods used to interface with the registered factories. */
  const char *
  GetITKSourceVersion() const override;

  const char *
  GetDescription() const override;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(BioRadImageIOFactory);

  /** Register one factory of this type  */
  static void
  RegisterOneFactory()
  {
    auto bioradFactory = BioRadImageIOFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(bioradFactory);
  }

protected:
  BioRadImageIOFactory();
  ~BioRadImageIOFactory() override;
};
} // end namespace itk

#endif
