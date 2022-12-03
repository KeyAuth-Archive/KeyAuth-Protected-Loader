#pragma once
#include <string>
#include "xor.hpp"



using namespace KeyAuth;


namespace Api {
	std::string name = xorstr_(""); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
	std::string ownerid = xorstr_(""); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
	std::string secret = xorstr_(""); // app secret, the blurred text on licenses tab and other tabs
	std::string version = xorstr_("1.0"); // leave alone unless you've changed version on website
	std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting



	api KeyAuthApp(name, ownerid, secret, version, url);

}

