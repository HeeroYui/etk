/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/uri/provider/provider.hpp>

namespace etk {
	namespace uri {
		namespace provider {
			class ProviderFile : public etk::uri::provider::Interface {
				protected:
					etk::Path m_offset;
				public:
					ProviderFile();
					ProviderFile(const etk::Path& _offset);
				public:
					ememory::SharedPtr<etk::io::Interface> create(const etk::Uri& _uri) override;
					bool exist(const etk::Uri& _uri) override;
					bool isDirectory(const etk::Uri& _uri) override;
					bool isFile(const etk::Uri& _uri) override;
					bool isSymLink(const etk::Uri& _uri) override;
					etk::Vector<etk::Uri> list(const etk::Uri& _uri) override;
					etk::Vector<etk::Uri> listRecursive(const etk::Uri& _uri) override;
					bool canMove() override;
					bool move(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) override;
					bool canCopy() override;
					bool copy(const etk::Uri& _uriSource, const etk::Uri& _uriDestination) override;
					bool canRemove() override;
					bool remove(const etk::Uri& _uri) override;
			};
		}
	}
}
