/*
 * RmdDiscoveredTemplateItem.java
 *
 * Copyright (C) 2009-14 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant
 * to the terms of a commercial license agreement with RStudio, then
 * this program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */
package org.rstudio.studio.client.rmarkdown.ui;

import org.rstudio.studio.client.rmarkdown.model.RmdDiscoveredTemplate;

import com.google.gwt.dom.client.Style;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.Label;

public class RmdDiscoveredTemplateItem extends Composite
{
   public RmdDiscoveredTemplateItem(RmdDiscoveredTemplate template)
   {
      template_ = template;
      panel_ = new HTMLPanel("");
      Label pkg = new Label(template.getPackage());
      pkg.getElement().getStyle().setFloat(Style.Float.RIGHT);
      pkg.getElement().getStyle().setColor("#909090");
      panel_.add(pkg);
      Label name = new Label(template.getName());
      panel_.add(name);
      
      initWidget(panel_);
   }
   
   public RmdDiscoveredTemplate getTemplate()
   {
      return template_;
   }
   
   private HTMLPanel panel_;
   private RmdDiscoveredTemplate template_;
}