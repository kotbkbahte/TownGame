#include "Framebuffer.h"

int SetupRenderToTexture(TGraphics* Graphics, int w, int h)
{
    glGenFramebuffers(1, &Graphics->m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, Graphics->m_Framebuffer);
    //Next we create a texture image that we attach as a color attachment to the framebuffer. We set the texture's dimensions equal to the width and height of the window and keep its data uninitialized:


    // generate texture
    glGenTextures(1, &Graphics->m_TextureTarget);
    glBindTexture(GL_TEXTURE_2D, Graphics->m_TextureTarget);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Graphics->m_TextureTarget, 0);
    //We also want to make sure OpenGL is able to do depth testing (and optionally stencil testing) so we have to make sure to add a depth (and stencil) attachment to the framebuffer. Since we'll only be sampling the color buffer and not the other buffers we can create a renderbuffer object for this purpose.

    //Creating a renderbuffer object isn't too hard. The only thing we have to remember is that we're creating it as a depth and stencil attachment renderbuffer object. We set its internal format to GL_DEPTH24_STENCIL8 which is enough precision for our purposes:


    glGenRenderbuffers(1, &Graphics->m_Renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, Graphics->m_Renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //Once we've allocated enough memory for the renderbuffer object we can unbind the renderbuffer.
    //Then, as a final step before we complete the framebuffer, we attach the renderbuffer object to the depth and stencil attachment of the framebuffer:

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, Graphics->m_Renderbuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer is not complete!");
        return False;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return True;
}
