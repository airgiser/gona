/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_GL_RENDERER_H
#define GONA_GRAPHICS_GL_RENDERER_H

#ifdef GONA_FOR_WIN
#include <Windows.h>
#include <GL/GL.h>
#elif GONA_FOR_UNIX
#include <GL/glx.h>
#elif GONA_FOR_MAC
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

#include "GnRenderer.h"
#include "GnGLContext.h"
#include "GnGLFontManager.h"

typedef struct gl_vertex {
  GLfloat position[2];
  GLfloat texCoord[2];
  GLfloat color[4];
} GL_Vertex;

/** \class GnGLRenderer
 *
 *  A GPU Renderer.
 */
class GnGLRenderer : public GnRenderer {
public:
  /**
   * Default Construtor.
   */
  GnGLRenderer();

  /**
   * Construct a Renderer with a specified Context.
   */
  GnGLRenderer(GnGLContext *context);

  /**
   * Destructor.
   */
  virtual ~GnGLRenderer();

public:
  /**
   * Erases the entire canvas to the specified color.
   *
   * @param color the specified color used to clear background
   */
  virtual void clear(GnColor color);

  /**
   * Transfer the buffer bits to device.
   */
  virtual void swapBuffers();

  /**
   * Sets the current paint which used to draw shaps, texts etc.
   *
   * @param paint a new paint
   */
  virtual void setPaint(const GnPaint &paint);

  /**
   * Draw a polyline.
   *
   * @param points the vertices of the polyline
   * @param num the num of vertices of the polyline
   */
  virtual void drawPolyLine(const GnPoint *points, int num);

  /**
   * Draw a polygon.
   *
   * @param points the vertices of the polygon
   * @param num the num of vertices of the polygon
   */
  virtual void drawPolygon(const GnPoint *points, int num);

  /**
   * Draw the specified image.
   *
   * @param image the image to be drawn
   * @param left the position of the left side of the image
   * @param top the position of the top side of the image
   */
  virtual void drawImage(const GnImage &image, int left, int top);

  /**
   * Draw the specified text.
   *
   * @param x the x-coordinate of the origin of the text
   * @param y the y-coordinate of the origin of the text
   * @param text the text to be drawn
   * @param len the length of the text
   */
  virtual void drawText(const wchar_t *text, size_t len, int x, int y);

protected:
  /**
   * Load a two-dimensional texture image
   *
   * @param[in] image the specified two-dimensional image
   * @param[out] textureWidth returns the width of texture image
   * @param[out] textureHeight returns the height of texture image
   * @return a named texture
   */
  GLuint loadTexture(const GnImage &image, size_t &textureWidth, size_t &textureHeight);

  /**
   * Inflate the vertex buffer.
   */
  void inflateVtxBuf(unsigned int newSize);

  /**
   * Generate anti-alised line texture
   */
  void genAALineTexture();

  /**
   * Gets the internal pixel format defined by OpenGL
   */
  static GLint getGLPixelFormat(GnPixelFormat pixfmt);

  /**
   * returns the smallest power of two that is greater than or equal to the value 
   */
  static int nextPower2(int value);

private:
  GnGLContext*    m_context;

  GnGLFontManager m_fontMgr;
  unsigned int    m_textSize;
  GnPaint         m_paint;

  unsigned int    m_vtxBufSize;
  GL_Vertex*      m_vtxBuf;

  GLuint          m_aaLineTexture;
};

#endif // GONA_GRAPHICS_GL_RENDERER_H
