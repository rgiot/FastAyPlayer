#ifndef __FAP__CONFIG__H
#define __FAP__CONFIG__H

#include <string>

class Fap;


/// @brief  Handle the configuration of a conversion
///
/// It is up to the caller to take care filename are alive all along the use of the config
class FapConfig {
	public:
		float threshold;

		char* srcFile;
		char* dstFile;

	 	bool print;
	
		FapConfig(): threshold{0}, srcFile{nullptr}, dstFile{nullptr}, print{true} {
	
		}

		Fap instantiate();
	};


enum class FapResultCode {
	Ok,
	CannotLoadInputFile,
	UnknownError
};

class FapPayload {
	private: 
	/// TODO replace the string by its data
	std::string output;

	public:

	FapPayload(): output{} {

	}

	FapPayload(std::string output): output{output} {

	}

	/// TODO generate the string here
	const std::string& repr() const {
		return this->output;
	}
};

class FapResult {
public:
	FapResultCode code;
	FapPayload payload;

	FapResult(FapResultCode code): code{code} {

	}

	FapResult(FapResultCode code, FapPayload payload): code{code}, payload{payload} {

	}
};




class Fap {
	private:
		FapConfig config;

	public:
		Fap(FapConfig config): config{config}{

		}

		/// @brief  Does the conversion
		///
		/// There is no error handling ATM. It is up to the caller to assume the configuration is correct
		FapResult handle();
};

#endif