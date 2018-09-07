/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/fs/Type.hpp>
#include <etk/String.hpp>
#include <etk/Map.hpp>
#include <etk/uri/Query.hpp>
#include <etk/fs/Path.hpp>


namespace etk {
	namespace uri {
		class IoProviderInterface : public ememory::EnableSharedFromThis<IoProvider> {
			public:
				
		};
		void addProvider(const etk::String& _scheme, ememory::SharedPtr<IoProviderInterface> _interface);
		void removeProvider(const etk::String& _scheme);
		ememory::SharedPtr<etk::io::Interface> provideIO(const etk::uri::Uri& _uri);
	}
}
