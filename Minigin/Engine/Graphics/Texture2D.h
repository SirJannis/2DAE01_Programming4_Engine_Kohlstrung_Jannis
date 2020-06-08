#pragma once
struct SDL_Texture;
namespace MyEngine
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	//Make a Wrapper around the texture2d animatedtexture
	//Drawwidth, drawheight, currentframe, isanimated, pivot, frametime(how long 1 frame is), currenttime, rows & columns
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		void SetTexture(SDL_Texture* newTexture);
	private:
		SDL_Texture* m_Texture;
	};
}
