/** @file
 * @author Edouard DUPIN
 * @copyright 2018, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <etk/uri/provider/Interface.hpp>

uint64_t etk::uri::provider::Interface::fileSize(const etk::Uri& _uri) {
	auto fileIO = create(_uri);
	if (fileIO == null) {
		return 0;
	}
	return fileIO->size();
}
