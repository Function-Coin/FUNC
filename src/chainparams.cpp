// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The CryptoDev developers
// Copyright (c) 2019 The FunCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (    0, uint256("00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"))
    (   65, uint256("00000045f6594d23790b2eb4608ed95d36cc99d1ede86abdbffe1d8d46439b04"))
    (22975, uint256("7e3c569aeb630b230570790824fdcaa534de6e279f257947f0cbd6417056320f"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1558088238, // * UNIX timestamp of last checkpoint block
    46895,      // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1555092104,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1555092104,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x3d;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xd1;
        pchMessageStart[3] = 0xb7;
        vAlertPubKey = ParseHex("0000056a3efcbaadef23fac7356a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nDefaultPort = 12280;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // FUNC starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 999999999;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 130; // FUNC: 2 minutes
        nTargetSpacing = 1 * 130;  // FUNC: 2 minutes
        nMaturity = 50;
        nStakeMinAge = 120 * 60;   // FUNC: 2 hours
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 20000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nFuncBadBlockTime = 1555246870; // Skip nBit validation of Block 259201 per PR #915
        nFuncBadBlocknBits = 489601702; // Skip nBit validation of Block 259201 per PR #915
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 205;
        nZerocoinStartTime = 1555351304; // October 17, 2017 4:30:00 AM
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 220; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nBlockDoubleAccumulated = 10;
        nEnforceNewSporkKey = 1555092104; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1527811200; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        // Public coin spend enforcement
        nPublicZCSpends = 225;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0 * COIN;   // zerocoin supply at block nFakeSerialBlockheightEnd

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "FunCoin - powered by CryptoDevs.co.uk and CDEV coin. Provider of quality wallets and related services.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83d5233cde562f7d47eddd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1555092104;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 482702;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"));
        assert(genesis.hashMerkleRoot == uint256("0x10297aaf75aa9c0a2bda02aa644b0f35149a644bc056e029c837d263c7a45c1f"));

        vSeeds.push_back(CDNSSeedData("funcseed.cdev.services", "funcseed.cdev.services"));     // Primary DNS Seeder from CryptoDev
        vSeeds.push_back(CDNSSeedData("108.61.166.242", "108.61.166.242"));      		// Single node address
        vSeeds.push_back(CDNSSeedData("199.247.25.78", "199.247.25.78"));        		// Single node address
        vSeeds.push_back(CDNSSeedData("95.179.137.186", "95.179.137.186"));          		// Single node address
        vSeeds.push_back(CDNSSeedData("45.32.234.201", "45.32.234.201"));         		// Single node address
        vSeeds.push_back(CDNSSeedData("95.179.147.180", "95.179.147.180"));        		// Single node address

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 130);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 113);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkKey = "047d5232a7821439ef4f477014cb09cf857c82c580ff676825d955d78557ee3927fd2decb96326f93ffb917d37a409e09e86b7eb318a68207c0dd9812d69798937";
        strSporkKeyOld = "047d5232a7821439ef4f477014cb09cf857c82c580ff676825d955d78557ee3927fd2decb96326f93ffb917d37a409e09e86b7eb318a68207c0dd9812d69798937";
        strObfuscationPoolDummyAddress = "fUbsSJD7HXMRrXh2PsuCzrNVkm4R7dMxoK";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 0; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 100; //The required confirmations for a zfunc to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xc7;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x3d;
        vAlertPubKey = ParseHex("000016efb4ead12cf322fe93762dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 12282;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 130; // FUNC: 1 day
        nTargetSpacing = 1 * 130;  // FUNC: 1 minute
        nLastPOWBlock = 200;
        nFuncBadBlockTime = 1489001494; // Skip nBit validation of Block 259201 per PR #915
        nFuncBadBlocknBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 999999999; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 20000000 * COIN;
        nZerocoinStartHeight = 205;
        nZerocoinStartTime = 1555351304;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 220; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1555092104; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        // Public coin spend enforcement
        nPublicZCSpends = 225;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1555092104;
        genesis.nNonce = 482702;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("cryptodevs.co.uk", "func-testnet.seed.cryptodevs.co.uk"));
        vSeeds.push_back(CDNSSeedData("cryptodevs.co.uk", "func-testnet.seed2.cryptodevs.co.uk"));
        vSeeds.push_back(CDNSSeedData("cryptodevs.co.uk", "testnet.dnsseed.func.cryptodevs.co.uk"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet func addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet func script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet func BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet func BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet func BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkKey = "049e331e8707db73693b814b6d9ca8809ab749e733b631734ad37511694ff1292815d592b79643cc45b4ed017878b7c815ccb6764162fba656f8bfe92bc8daedcc";
        strSporkKeyOld = "049e331e8707db73693b814b6d9ca8809ab749e733b631734ad37511694ff1292815d592b79643cc45b4ed017878b7c815ccb6764162fba656f8bfe92bc8daedcc";
        strObfuscationPoolDummyAddress = "y54tbsdhLYpy9f8kxgiNL3YAUrcvk5Vb5x";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0x3e;
        pchMessageStart[3] = 0xb6;
        nDefaultPort = 12284;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // FUNC: 1 day
        nTargetSpacing = 1 * 130;        // FUNC: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 50;
        nStakeMinAge = 0;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 20000000 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1555351304;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

        // Public coin spend enforcement
        nPublicZCSpends = 225;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1555092104;
        genesis.nNonce = 482702;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000eb5ce620a18004137ab749c3c604f9fb202c3a536efba866ec81231ef09"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        strSporkKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 12286;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
