/*
 * Copyright © 2013 ARM Limited.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "../drmmode_driver.h"
#include <stddef.h>
#include <xf86drmMode.h>
#include <sys/ioctl.h>

struct drm_exynos_plane_set_zpos {
	__u32 plane_id;
	__s32 zpos;
};

#define DRM_EXYNOS_PLANE_SET_ZPOS 0x06
#define DRM_IOCTL_EXYNOS_PLANE_SET_ZPOS DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_PLANE_SET_ZPOS, struct drm_exynos_plane_set_zpos)

static int init_plane_for_cursor(int drm_fd, uint32_t plane_id)
{
	struct drm_exynos_plane_set_zpos data;

	data.plane_id = plane_id;
	data.zpos = 1;

	return ioctl(drm_fd, DRM_IOCTL_EXYNOS_PLANE_SET_ZPOS, &data);
}

struct drmmode_interface exynos_interface = {
	0x00000001 /* dumb_scanout_flags */,
	0x00000001 /* dumb_no_scanout_flags */,
	1 /* use_page_flip_events */,
	init_plane_for_cursor /* init_plane_for_cursor */
};

struct drmmode_interface *drmmode_interface_get_implementation(int drm_fd)
{
	return &exynos_interface;
}
