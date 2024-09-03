#include "CsvLoad.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>

CsvLoad* CsvLoad::m_instance = nullptr;

namespace
{
	// csvデータの,で文字列を分割する
	std::vector<std::string> Split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		while (getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}

	const std::string kFrontPathName = "data/csv/";
	const std::string kBackPathName = ".csv";
}

void CsvLoad::StatusLoad(CharacterBase::Status& data, const char* charcterName)
{
	// 一時保存用string
	std::string strBuf;
	// カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	// ファイル読み込み
	std::ifstream ifs("data/csv/status.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	//情報を取得できたかどうかのフラグ
	bool isGet = false;

	//最初は対応表情報が入っているだけなので無視する
	std::getline(ifs, strBuf);

	while (getline(ifs, strBuf))
	{
		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');

		//[0]:キャラクター名
		//[1]:体力
		//[2]:攻撃力
		//[3]:防御力
		//[4]:移動速度
		//[5]:死亡時のポイント

		//指定したキャラクター名と一致するデータがあれば情報を取得する
		if (strConmaBuf[LoadData::eStatusOrder::name] == charcterName)
		{
			isGet = true;
			data.hp = std::stoi(strConmaBuf[LoadData::eStatusOrder::hp]);
			data.atk = std::stoi(strConmaBuf[LoadData::eStatusOrder::atk]);
			data.def = std::stoi(strConmaBuf[LoadData::eStatusOrder::def]);
			data.speed = std::stof(strConmaBuf[LoadData::eStatusOrder::speed]);
			data.point = std::stoi(strConmaBuf[LoadData::eStatusOrder::point]);
		}
	}

	//情報を取得できなかった時、エラーを吐くようにする
	//取得できなかった理由想定
	//�@キャラクター名がスペルミスや大文字小文字の違いで異なる
	//�Acsvに情報を追加し忘れている
	if (!isGet)
	{
		assert(0 && "指定したキャラクター名の情報を取得できませんでした");
	}

	return;
}

void CsvLoad::StageEnenyDataLoad(const char* stageName, std::list<std::shared_ptr<EnemyManager::EnemyGenerateInfo>>& pGenerateInfo)
{
	// 一時保存用string
	std::string strBuf;
	// カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	std::string csvName = kFrontPathName + stageName + kBackPathName;

	// ファイル読み込み
	std::ifstream ifs(csvName);
	if (!ifs)
	{
		assert(false);
		return;
	}

	//最初は対応表情報が入っているだけなので無視する
	std::getline(ifs, strBuf);

	while (getline(ifs, strBuf))
	{
		//取得した文字列をカンマ区切りの配列(情報群)にする
		strConmaBuf = Split(strBuf, ',');

		//[0]:生成する敵のID(名前)
		//[1]:生成フェーズ
		//[2]:生成フレーム
		//[3]:生成位置

		std::shared_ptr<EnemyManager::EnemyGenerateInfo> add = std::make_shared<EnemyManager::EnemyGenerateInfo>();
		add->enemyName = strConmaBuf[LoadData::eStageOrder::ID];
		add->appearPhase = std::stoi(strConmaBuf[LoadData::eStageOrder::phase]);
		add->appearFrame = std::stoi(strConmaBuf[LoadData::eStageOrder::frame]);
		add->appearPos = std::stoi(strConmaBuf[LoadData::eStageOrder::AppearanceLocation]);

		pGenerateInfo.emplace_back(add);
	}

	return;
}
