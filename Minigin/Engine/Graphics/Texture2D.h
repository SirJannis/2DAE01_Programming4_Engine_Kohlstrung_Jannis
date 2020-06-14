#pragma once
struct SDL_Texture;
namespace MyEngine
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		void SetPath(const std::string& path) { m_Path = path; }
		const std::string& GetPath()const { return m_Path; }

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		void SetTexture(SDL_Texture* newTexture);
	private:
		SDL_Texture* m_Texture;
		std::string m_Path;
	};
}
