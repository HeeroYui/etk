
/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/uri/provider/provider.hpp>
#include <etk/archive/Archive.hpp>
#include <ememory/SharedPtr.hpp>

namespace etk {
	namespace uri {
		namespace provider {
			class ProviderFileZip : public etk::uri::provider::Interface {
				protected:
					ememory::SharedPtr<etk::Archive> m_archive;
					etk::Path m_offset;
					void loadZipFile(const etk::Uri& _zipFile);
				public:
					ProviderFileZip(const etk::Uri& _zipFile);
					ProviderFileZip(const etk::Uri& _zipFile, const etk::Path& _offset);
				public:
					ememory::SharedPtr<etk::io::Interface> create(const etk::Uri& _uri) override;
					bool exist(const etk::Uri& _uri) override;
					bool isDirectory(const etk::Uri& _uri) override;
					bool isFile(const etk::Uri& _uri) override;
					bool isSymLink(const etk::Uri& _uri) override;
					etk::Vector<etk::Uri> list(const etk::Uri& _uri) override;
					etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) override;
			};
		}
	}
}
