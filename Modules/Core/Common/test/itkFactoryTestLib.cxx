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
#include "itkFactoryTestLib.h"
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkVersion.h"

static unsigned long itkTotalMemoryUsed = 0;

template <typename TElementIdentifier, typename TElement>
class TestImportImageContainer : public itk::ImportImageContainer<TElementIdentifier, TElement>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(TestImportImageContainer);

  /** Standard class type aliases.   */
  using Self = TestImportImageContainer;
  using Superclass = itk::ImportImageContainer<TElementIdentifier, TElement>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(TestImportImageContainer);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(TestImportImageContainer);

  using typename Superclass::ElementIdentifier;
  using typename Superclass::Element;

  // Methods from itkObject
  virtual ~TestImportImageContainer()
  {
    itkTotalMemoryUsed -= m_TotalSize;
    m_TotalSize = 0;
    DeallocateManagedMemory();
  }
  TestImportImageContainer()
    : m_TotalSize(0)

  {}

protected:
  TElement *
  AllocateElements(ElementIdentifier size, bool) const override
  {
    std::cout << "TestImportImageContainer: Allocating " << size << " elements of type " << typeid(TElement).name()
              << " totaling " << sizeof(TElement) * size << " bytes" << std::endl;

    TElement * data;
    try
    {
      data = new Element[size];
    }
    catch (...)
    {
      // We cannot construct an error string here because we may be out
      // of memory.  Do not use the exception macro.
      throw itk::MemoryAllocationError(__FILE__, __LINE__, "Failed to allocate memory for image.", ITK_LOCATION);
    }

    m_TotalSize = size * sizeof(TElement);
    itkTotalMemoryUsed += m_TotalSize;

    m_MemoryAllocatedByTestImportImageContainer = true;

    std::cout << "TestImportImageContainer: Total memory used is " << itkTotalMemoryUsed << " bytes" << std::endl;

    return data;
  }

  void
  DeallocateManagedMemory() override
  {
    std::cout << "TestImportImageContainer: Deallocating " << this->Capacity() << " elements of type "
              << typeid(TElement).name() << " totaling " << sizeof(TElement) * this->Capacity() << " bytes"
              << std::endl;

    if (m_MemoryAllocatedByTestImportImageContainer)
    {
      delete[] this->GetImportPointer();
      this->SetImportPointer(0);
      this->SetCapacity(0);
      this->SetSize(0);
    }
    else
    {
      Superclass::DeallocateManagedMemory();
    }

    std::cout << "TestImportImageContainer: Total memory used is " << itkTotalMemoryUsed << " bytes" << std::endl;
  }

private:
  mutable TElementIdentifier m_TotalSize;

  mutable bool m_MemoryAllocatedByTestImportImageContainer{ false };
};

class ImportImageContainerFactory : public itk::ObjectFactoryBase
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImportImageContainerFactory);

  using Self = ImportImageContainerFactory;
  using Superclass = itk::ObjectFactoryBase;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Class methods used to interface with the registered factories. */
  const char *
  GetITKSourceVersion() const override
  {
    return ITK_SOURCE_VERSION;
  }
  const char *
  GetDescription() const override
  {
    return "A Factory for ImportImageContainer";
  }

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ImportImageContainerFactory);

  /** Register one factory of this type  */
  static void
  RegisterOneFactory()
  {
    auto factory = ImportImageContainerFactory::New();
    itk::ObjectFactoryBase::RegisterFactory(factory);
  }

private:
#define OverrideTypeMacro(t)                                                         \
  this->RegisterOverride(typeid(itk::ImportImageContainer<unsigned long, t>).name(), \
                         typeid(TestImportImageContainer<unsigned long, t>).name(),  \
                         "Test ImportImageContainerOverride",                        \
                         true,                                                       \
                         itk::CreateObjectFunction<TestImportImageContainer<unsigned long, t>>::New())


  ImportImageContainerFactory()
  {
    OverrideTypeMacro(short);
    OverrideTypeMacro(unsigned char);
    OverrideTypeMacro(float);
    OverrideTypeMacro(int);
    OverrideTypeMacro(long long);
    OverrideTypeMacro(double);
    OverrideTypeMacro(itk::RGBPixel<unsigned char>);
    OverrideTypeMacro(itk::RGBPixel<unsigned short>);
  }
};

/**
 * Routine that is called when the shared library is loaded by
 * itk::ObjectFactoryBase::LoadDynamicFactories().
 *
 * itkLoad() is C (not C++) function.
 */
static ImportImageContainerFactory::Pointer staticImportImageContainerFactory;
itk::ObjectFactoryBase *
itkLoad()
{
  staticImportImageContainerFactory = ImportImageContainerFactory::New();
  return staticImportImageContainerFactory;
}
