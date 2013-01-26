#pragma once

#include "CmPrerequisites.h"
#include "CmIReflectable.h"
#include "CmCoreGpuObject.h"

namespace CamelotEngine
{
	/**
	 * @brief	Base class for all resources used in the engine.
	 */
	class CM_EXPORT Resource : public IReflectable, public CoreGpuObject
	{
	public:
		Resource();
		virtual ~Resource() {};

		const String& getUUID() const { return mUUID; }

		/**
		 * @brief	Returns true if the object has been properly initialized. You are not
		 * 			allowed to call any methods on the resource until you are sure resource is initialized.
		 */
		bool isInitialized() const { return mIsInitialized; }

		/**
		 * @brief	Blocks the current thread until the resource is fully initialized.
		 */
		void waitUntilInitialized();

	protected:
		friend class Resources;
		
		/**
		 * @brief	Finishes up resource initialization. Usually called right after the resource is created.
		 * 			Make sure that derived classes implement their own initialize_internal, and make sure
		 * 			they call this implementation from it.
		 */
		virtual void initialize_internal();

		/**
		 * @copydoc CoreGpuObject::destroy_internal()
		 */
		virtual void destroy_internal();

		/**
		 * @brief	Marks the resource as initialized.
		 */
		void setInitialized() { mIsInitialized = true; }

		String mUUID; 
		UINT32 mSize;

		// Transient
		bool mIsInitialized;

		CM_STATIC_THREAD_SYNCHRONISER(mResourceLoadedCondition)
		CM_STATIC_MUTEX(mResourceLoadedMutex)

	/************************************************************************/
	/* 								SERIALIZATION                      		*/
	/************************************************************************/
	public:
		friend class ResourceRTTI;
		static RTTITypeBase* getRTTIStatic();
		virtual RTTITypeBase* getRTTI() const;
	};
}