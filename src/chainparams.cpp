// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "neoscrypt.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
void MineGenesis(CBlock genesis){
    // This will figure out a valid hash and Nonce if you're creating a different genesis block:
    uint256 hashTarget = CBigNum().SetCompact(Params().ProofOfWorkLimit().GetCompact()).getuint256();
    printf("Target: %s\n", hashTarget.GetHex().c_str());
    uint256 newhash = genesis.GetHash();
    uint256 besthash;
    memset(&besthash,0xFF,32);
    while (newhash > hashTarget) {
    	++genesis.nNonce;
        if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time");
            ++genesis.nTime;
        }
	newhash = genesis.GetHash();
	if(newhash < besthash){
	    besthash=newhash;
	    printf("New best: %s\n", newhash.GetHex().c_str());
	}
    }
    printf("Found Genesis, Nonce: %ld, Hash: %s\n", genesis.nNonce, genesis.GetHash().GetHex().c_str());
    printf("Gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
}
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xb5;
		pchMessageStart[1] = 0xfa;
		pchMessageStart[2] = 0xdd;
		pchMessageStart[3] = 0x72;
		vAlertPubKey = ParseHex("01a983220fc7a38a7106332003fef77896538a382adfac389cc45f3c98751d9af354a097776757576259351a98a8aca628a1fd645c3232678c5845384c781cf8db");
		nDefaultPort = 8557;
		nRPCPort = 8558;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		const char* pszTimestamp = "CatoCoin";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1529172125, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1529205537;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 212322;
		hashGenesisBlock = genesis.GetHash();
		//MineGenesis(genesis);
/*
          uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
               {
                   ++genesis.nNonce;
                   if (genesis.nNonce == 0)
                   {
                       printf("NONCE WRAPPED, incrementing time");
                       ++genesis.nTime;
                   }
               }
        }
        genesis.print();
        printf("genesis.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        printf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
*/
/*

        printf("Generating genesis block...\n");
        uint32_t nounce = 1;
		while(1) {
            //printf("Nounce: %d\n", nounce);
			genesis.nNonce = nounce;
			hashGenesisBlock = genesis.GetHash();
			
			if(hashGenesisBlock.GetHex() < std::string("0000ffffff000000000000000000000000000000000000000000000000000000")) {
			//if(hashGenesisBlock.GetHex() < bnProofOfWorkLimit.GetHex()) {
			//if(consensus.hashGenesisBlock.GetHex() < std::string("0000082da923a04678394f873852c7f08b777af30224b6e23296f586370e80ae")) {
				printf("nounce: %x\n",nounce);
				break;
			} else {
				if( nounce % 10000 == 0)
					printf("nounce: %x, hash: %s, merklehash:%s\n",nounce, hashGenesisBlock.GetHex().c_str(),genesis.hashMerkleRoot.ToString().c_str());
				++nounce;
			}
		} 
		
        printf("genesis: %s\n",hashGenesisBlock.GetHex().c_str());
        printf("merklehash: %s\n",genesis.hashMerkleRoot.ToString().c_str());
*/
/*
	 //////////////
        //////////////
                // calculate Genesis Block
                // Reset genesis
                hashGenesisBlock = uint256S("0x");
                std::cout << std::string("Begin calculating Mainnet Genesis Block:\n");
                if (true && (genesis.GetHash() != hashGenesisBlock)) {
                    LogPrintf("Calculating Mainnet Genesis Block:\n");
                    arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
                    uint256 hash;
                    genesis.nNonce = 0;
                    // This will figure out a valid hash and Nonce if you're
                    // creating a different genesis block:
                    // uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                    // hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow).getuint256();
                    // while (genesis.GetHash() > hashTarget)
                    while (UintToArith256(genesis.GetHash()) > hashTarget)
                    {
                        ++genesis.nNonce;
                        if (genesis.nNonce == 0)
                        {
                            LogPrintf("NONCE WRAPPED, incrementing time");
                            std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                            ++genesis.nTime;
                        }
                        if (genesis.nNonce % 10000 == 0)
                        {
                            LogPrintf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                            // std::cout << strNetworkID << " nonce: " << genesis.nNonce << " time: " << genesis.nTime << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
                        }
                    }
                    std::cout << "Mainnet ---\n";
                    std::cout << "  nonce: " << genesis.nNonce <<  "\n";
                    std::cout << "   time: " << genesis.nTime << "\n";
                    std::cout << "   hash: " << genesis.GetHash().ToString().c_str() << "\n";
                    std::cout << "   merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
                    // Mainnet --- nonce: 296277 time: 1390095618 hash: 000000bdd771b14e5a031806292305e563956ce2584278de414d9965f6ab54b0
                }
                std::cout << std::string("Finished calculating Mainnet Genesis Block:\n");
*/
/*
        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        uint256 thash;
        unsigned int profile = 0x0;
        while(true){
            neoscrypt((unsigned char *) &genesis.nVersion, (unsigned char *) &thash, profile);
            if (thash <= hashTarget) break;
            if ((genesis.nNonce & 0xFFF) == 0){
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());}
            ++genesis.nNonce;
            if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time\n");
            ++genesis.nTime;}
        }
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
	
*/
        // If genesis block hash does not match, then generate new genesis hash.
/*       if (5==5)
       {
           printf("Searching for genesis block...\n");
           // This will figure out a valid hash and Nonce if you're
           // creating a different genesis block:
           uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
           uint256 thash;
           char scratchpad[131583];

           while(5==5)
           {
               scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
               if (thash <= hashTarget)
                   break;
               if ((genesis.nNonce & 0xFFF) == 0)
               {
                   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
               }
               ++genesis.nNonce;
               if (genesis.nNonce == 0)
               {
                   printf("NONCE WRAPPED, incrementing time\n");
                   ++genesis.nTime;
               }
           }
           printf("genesis.nTime = %u \n", genesis.nTime);
           printf("genesis.nNonce = %u \n", genesis.nNonce);
           printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
       }


        genesis.print();

*/
	assert(hashGenesisBlock == uint256("00008da2e6557bcea78889b2e02f63a5cf2a750e8468313b82d5e53529651792"));
		assert(genesis.hashMerkleRoot == uint256("c77ea48f94118258717192fa4d6a71792ed06db0e8a6cd5c1e134da8c65532f3"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 156);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		//vSeeds.push_back(CDNSSeedData("0", "139.99.98.127")); //Add seed IP
		//vSeeds.push_back(CDNSSeedData("1", "139.99.98.128")); //Add seed IP
		//vSeeds.push_back(CDNSSeedData("2", "139.99.98.129")); //Add seed IP

		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		strDarksendPoolDummyAddress = "P8CA654Df1sxw132M3dw865f1FgCX26l1a";
		nLastPOWBlock = 1000;
		nPOSStartBlock = 101;
		nMasternodePaymentStartBlock = 101;
	
	}

	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x13;
		pchMessageStart[1] = 0xfe;
		pchMessageStart[2] = 0xb7;
		pchMessageStart[3] = 0x36;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("01f983220fc7a38a7106332003fef77896538a382adfac389cc45f3c98751d9af354a097776757576259351a98a8aca628a1fd645c3232678c5845384c781cf8db");
		nDefaultPort = 9557;
		nRPCPort = 9558;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 520159231;
		genesis.nNonce = 0;

		//assert(hashGenesisBlock == uint256("0x0000d9badf5d39afaa47451111a931672baaa3ce9bbbfb9165f414b9e6e69d61"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}
